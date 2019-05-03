/**
 * File: tcp_server.c for project Xserver
 * Email: xeapplee@gmail.com
 * website: https://www.supjos.cn
 * Author: Josin 
 */

#include "tcp_server.h"
#include "../tools/string.h"
#include "../tools/list.h"
#include "../config.h"

int
/* Init the socket with the given host & port, or the following instruction:
 * This function use the IPv4 as default. or IPv6 if you like
 * host: NULL will let the kernel to use the 0.0.0.0 or INADDR_ANY
 * port: 0 will let the kernel to use the 8181
 * RETURN VALUE:
 * The server socket file descriptor */
xserver_init(const char *host, const int port)
{
	int _sock_fd, _result;

	_sock_fd = socket( PF_INET, SOCK_STREAM, 0 );
	assert( _sock_fd != -1 );

	_sockaddr server_addr;
	memset(&server_addr, 0, sizeof(_sockaddr));
	if (!port)
		server_addr.sin_port = htons((uint16_t) 8181);
	else
		server_addr.sin_port = htons((uint16_t) port);
	server_addr.sin_family = AF_INET;
	if (!host)
		server_addr.sin_addr.s_addr = INADDR_ANY;
	else
		server_addr.sin_addr.s_addr = inet_addr(host);
	_result = bind(_sock_fd, (const struct sockaddr*)&server_addr, sizeof(_sockaddr));
	assert( _result != -1 );

	_result = listen( _sock_fd, 1000 );
	assert( _result != -1 );

	return _sock_fd;
}

void *
/* Child thread to do the job with the thread_id the arg is empty pointer or thread_num
 * in kernel the thread id must use the arg not the pthread_self() return value
 * newly client fd come from _thread_data */
server_job_thread(void *arg)
{
	int _tid = *((int *)arg);
 
sleep_for_new_client:
 
	/* Wait signal and wakeup from sleep */
	pthread_cond_wait( &(_thread_cond[_tid]), &(_thread_mutex[_tid]) );
	
#ifdef __linux__
	int i, _next_pos, _ready;
    char *_buff, *_request_uri;
    list *__t, *stream_request_data;
	struct epoll_event ev[50];

	while ( true ) {
		/* Wait 60s until after timeout epoll_wait will return by code: 0 */
		_ready = epoll_wait(_thread_data[_tid], ev, 50, 60);

		if ( _ready ) {
			/* if event coming, loop events
			 * with the different events
			 * EPOLLIN: I/O read event
			 * EPOLLHUP: Peers close the connection */
			for (i = 0; i < 50; ++i) {

				if (ev[i].events & EPOLLIN) {
					/* EPOLLIN event comming */
					_buff = get_stream_from_socket(ev[i].data.fd);
					if (!strlen(_buff)) {
                        /* Read data number: 0
                         * means that the peers close the connection
                         * so remove it from the epoll queue */
                        free(_buff);
                        epoll_ctl(_thread_data[_tid], EPOLL_CTL_DEL, ev[i].data.fd, EMPTY_PTR);
                        continue;
					}
					
					/* Parse the http stream */
					stream_request_data = parse_http_stream(_buff, &_next_pos);
     
					/* Find the request uri. */
                    /* Get the request url, if the request url is / dlopen the default share library
                     * Default format: GET / HTTP/1.1
                     * RequestURI mapping rule: /dir/filename/function-name */
                    LIST_FOREACH_VAL(stream_request_data, __t) {
                        list_data *__k = (list_data *)__t->node.data_ptr;
                        if (strncasecmp(__k->name, "request_uri", 11) == 0) {
                            _request_uri = __k->value;
                        }
                    } LIST_FOREACH_END();

					/* Response the client with the string */
					/* The following block need be rewrite in the next version code. */
					char _buffer_data[200] =
					            "HTTP/1.1 200 OK\r\n"
                                "Content-Type:application/json;charset=utf-8\r\n"
		                        "Content-Length:26\r\n"
		                        "Connection: close\r\n"
		                        "\r\n";

					if ( strlen(_request_uri) == 1 && *_request_uri == '/' ) {
						void *handle = dlopen("../kernel/extensions/info.so", RTLD_NOW);
						FUNC f = (FUNC)dlsym(handle, "info");
						char *s = f();
						strncat(_buffer_data, s, strlen(s));
					} else {
						strncat(_buffer_data, "{\"server\":\"Xserver 0.1.3\"}", 26);
					}

					write(ev[i].data.fd, _buffer_data, strlen(_buffer_data));
					shutdown(ev[i].data.fd, SHUT_WR);
					
					/* Free the memory after used. */
					DESTROY_LIST(stream_request_data);
                    free(_buff);
				} else if (ev[i].events & (EPOLLHUP | EPOLLRDHUP)) {
					/* Remove fd from epoll wait queue. */
					epoll_ctl(_thread_data[_tid], EPOLL_CTL_DEL, ev[i].data.fd, EMPTY_PTR);
				}
			} /* end for */
		} /* end if ready */
		else
        {
            goto sleep_for_new_client;
        }
	} /* end while true */

#endif

	return EMPTY_PTR;
}

void
/* Init the sub-thread with the given thread_number or 0 to use the default number : 2
 * In default: there are only two thread: main thread and only child-thread
 * Main thread do the job assign the newly client to the sub-thread
 * Child thread do the client's connections from the main thread */
xserver_init_threads(const int thread_number)
{
    int i;
    
	for (i = 0; i < thread_number; ++i) {
		/* Pthread cond. */
		pthread_cond_init( &_thread_cond[i], EMPTY_PTR );

		/* Pthread mutex */
		pthread_mutex_init( &_thread_mutex[i], EMPTY_PTR );

		/* Initialise the _list data */
#if __linux__
		_thread_data[i] = epoll_create(1);
#endif
		/* Pthread id */
		_thread_id[i] = i;
		pthread_create(&_threads[i], EMPTY_PTR, server_job_thread, &_thread_id[i]);
	}

	/* Set the thread number to the given number */
	_thread_number = thread_number;
}

void
/*
 * To run the xserver main thread will only accept the client connection
 * each sub-thread will do the real job, after doing the job it will slept until newly client arrived. */
xserver_run( const int _sock_fd )
{
	int _client_fd, dispatch_id;
	_sockaddr client_addr;
	_sockaddr_len  client_addr_len;
#ifdef __linux__
	struct epoll_event ev;
#endif

	while ( true )
	{
		_client_fd = accept( _sock_fd, (struct sockaddr*)&client_addr, &client_addr_len );
		if ( _client_fd )
		{
			/* Assign the newly client to it's child-thread
			 * After assigning notify the thread to wake it up from sleepy state. */
			dispatch_id = _client_fd % _thread_number;

			LOG_INFO(LOG_ERROR_LEVEL, "new client: %d, dispatched to: %d\n", _client_fd, dispatch_id);

			/* Add the client fd to the thread_data _list */
#ifdef __linux__
			ev.events = EPOLLIN;
			ev.data.fd = _client_fd;
			epoll_ctl(_thread_data[dispatch_id], EPOLL_CTL_ADD, _client_fd, &ev);
#endif
			/* notify the thread */
			pthread_cond_signal(&_thread_cond[dispatch_id]);
		}
	}
}