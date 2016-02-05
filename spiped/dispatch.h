#ifndef _DISPATCH_H_
#define _DISPATCH_H_

#include <stdint.h>

/* Opaque structures. */
struct proto_secret;
struct sock_addr;

/**
 * dispatch_accept(s, tgt, rtime, sas, decr, nofps, requirefps, nokeepalive, K,
 *     nconn_max, timeo):
 * Start accepting connections on the socket ${s}.  Connect to the target
 * ${tgt}, re-resolving it every ${rtime} seconds if ${rtime} > 0; on address
 * resolution failure use the most recent successfully obtained addresses, or
 * the addresses ${sas}.  If ${decr} is 0, encrypt the outgoing connections; if
 * ${decr} is non-zero, decrypt the incoming connections.  Don't accept more
 * than ${nconn_max} connections.  If ${nofps} is non-zero, don't use perfect
 * forward secrecy.  If {$requirefps} is non-zero, require that both ends use
 * perfect forward secrecy.  Enable transport layer keep-alives (if applicable)
 * if and only if ${nokeepalive} is zero.  Drop connections if the handshake or
 * connecting to the target takes more than ${timeo} seconds.  Returns a
 * cookie which can be passed to dispatch_shutdown.
 */
void * dispatch_accept(int, const char *, double, struct sock_addr **, int, int,
    int, int, const struct proto_secret *, size_t, double);

/**
 * dispatch_shutdown(dispatch_cookie):
 * Stops and frees memory associated with the ${dispatch_cookie}.
 */
void dispatch_shutdown(void *);

#endif /* !_DISPATCH_H_ */
