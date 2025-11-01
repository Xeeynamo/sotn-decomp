/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspnet_inet.h - PSP networking libraries.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@0xd6.org>
 *
 * Portions based on PspPet's wifi_03 sample code.
 * 
 */

#ifndef PSPNET_INET_H
#define PSPNET_INET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/socket.h>
#include <sys/select.h>

/** 
 *  This struct is needed because tv_sec size is different from what newlib expect
 *  Newlib expects 64bits for seconds and PSP expects 32bits
 */
struct SceNetInetTimeval {
    uint32_t tv_sec;
    uint32_t tv_usec;
};

int sceNetInetInit(void);
int sceNetInetSelect(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct SceNetInetTimeval *timeout);
int sceNetInetTerm(void);
int sceNetInetGetErrno(void);
int	sceNetInetAccept(int s, struct sockaddr *addr, socklen_t *addrlen);
int	sceNetInetBind(int s, const struct sockaddr *my_addr, socklen_t addrlen);
int	sceNetInetConnect(int s, const struct sockaddr *serv_addr, socklen_t addrlen);
int	sceNetInetGetsockopt(int s, int level, int optname, void *optval, socklen_t *optlen);
int	sceNetInetListen(int s, int backlog);
size_t	sceNetInetRecv(int s, void *buf, size_t len, int flags);
size_t	sceNetInetRecvfrom(int s, void *buf, size_t flags, int, struct sockaddr *from, socklen_t *fromlen);
size_t	sceNetInetSend(int s, const void *buf, size_t len, int flags);
size_t	sceNetInetSendto(int s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen);
int	sceNetInetSetsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
int	sceNetInetShutdown(int s, int how);
int	sceNetInetSocket(int domain, int type, int protocol);
int sceNetInetClose(int s);
int sceNetInetGetErrno(void);
int	sceNetInetGetpeername(int s, struct sockaddr *name, socklen_t *namelen);
int	sceNetInetGetsockname(int s, struct sockaddr *name, socklen_t *namelen);
ssize_t sceNetInetSendmsg(int s, const struct msghdr *msg, int flags);
ssize_t sceNetInetRecvmsg(int s, struct msghdr *msg, int flags);

#ifdef __cplusplus
}
#endif

#endif /* PSPNET_INET_H */
