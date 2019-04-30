/**
 * File: xxx for project Xserver
 * Email: xeapplee@gmail.com
 * website: https://www.supjos.cn
 * Author: Josin 
 */

#ifndef XSERVER_TCP_SERVER_H
#define XSERVER_TCP_SERVER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#include "../config.h"

__BEGIN_DECL

typedef socklen_t _sockaddr_len;
typedef struct sockaddr_in _sockaddr;

/* Some function declarations
 * It can be used in C++ with the __BEGIN_DECL & __END_DECL */

/* Init. the socket and return the sock file descriptor,
 * if host if NULL or nullptr, 0.0.0.0 will be used.
 * port will be 8181 if 0 is passed */
int xserver_init(const char *host, int port);

/* Threads will be forked with the number: thread_number, maximum is 256
 * if you want to change it bigger, you must modify the source code. */
void xserver_init_threads(int thread_number);

/* Run the socket main thread will accept the connection
 * dispatch it to the child-thread */
void xserver_run( int _sock_fd );

__END_DECL

#endif /* XSERVER_TCP_SERVER_H */
