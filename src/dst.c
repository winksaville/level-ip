#include "syshead.h"
#include "dst.h"
#include "ip.h"
#include "arp.h"

int dst_neigh_output(struct sk_buff *skb)
{
    struct iphdr *iphdr = ip_hdr(skb);
    struct netdev *netdev = skb->netdev;
    uint8_t *dmac = arp_get_hwaddr(iphdr->daddr);
    int rc;

    if (dmac) {
        return netdev_transmit(skb, dmac, ETH_P_IP);
    } else {
        rc = arp_request(iphdr->saddr, iphdr->daddr, netdev);
        free_skb(skb);
        return rc;
    }
}
