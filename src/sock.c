#include "syshead.h"
#include "sock.h"
#include "socket.h"

struct sock *sk_alloc(struct net_ops *ops, int protocol)
{
    struct sock *sk;

    sk = ops->alloc_sock(protocol);

    sk->ops = ops;

    return sk;
}

void sock_init_data(struct socket *sock, struct sock *sk)
{

}
