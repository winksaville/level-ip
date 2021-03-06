#include "ethernet.h"
#include "icmpv4.h"
#include "ip.h"
#include "utils.h"

void icmpv4_incoming(struct sk_buff *skb) 
{
    struct iphdr *iphdr = ip_hdr(skb);
    struct icmp_v4 *icmp = (struct icmp_v4 *) iphdr->data;

    //TODO: Check csum

    switch (icmp->type) {
        case ICMP_V4_ECHO:
            icmpv4_reply(skb);
            break;
        default:
            perror("ICMPv4 did not match supported types");
            return;
    }
}

void icmpv4_reply(struct sk_buff *skb)
{
    struct iphdr *iphdr = ip_hdr(skb);
    struct icmp_v4 *icmp = (struct icmp_v4 *) iphdr->data;
    uint16_t icmp_len = iphdr->len - (iphdr->ihl * 4);

    skb_reserve(skb, ETH_HDR_LEN + IP_HDR_LEN + icmp_len);
    skb_push(skb, icmp_len);
        
    icmp->type = ICMP_V4_REPLY;
    icmp->csum = 0;
    icmp->csum = checksum(icmp, icmp_len, 0);

    iphdr->daddr = iphdr->saddr;

    skb->protocol = ICMPV4; 

    ip_output(NULL, skb);
}
