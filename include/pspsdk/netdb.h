/* Simple gethostbyname and gethostbyaddr replacements, note not thread safe */
#ifndef __NETDB_H__
#define __NETDB_H__

#ifdef __cplusplus
extern "C" {
#endif

#define	NETDB_INTERNAL	-1	/* see errno */
#define	NETDB_SUCCESS	0	/* no problem */
#define	HOST_NOT_FOUND	1 /* Authoritative Answer Host not found */
#define	TRY_AGAIN	2 /* Non-Authoritative Host not found, or SERVERFAIL */
#define	NO_RECOVERY	3 /* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
#define	NO_DATA		4 /* Valid name, no data record of requested type */
#define	NO_ADDRESS	NO_DATA		/* no address, look for MX record */

extern int h_errno;

struct hostent
{
	char *h_name;
	char **h_aliases;
	int  h_addrtype;
	int  h_length;
	char **h_addr_list;
	char *h_addr;
};

struct hostent *gethostbyaddr(const void *addr, int len, int type);
struct hostent *gethostbyname(const char *name);

#ifdef __cplusplus
}
#endif

#endif
