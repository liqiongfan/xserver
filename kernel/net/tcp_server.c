/**
 * File: tcp_server.c for project Xserver
 * Email: xeapplee@gmail.com
 * website: https://www.supjos.cn
 * Author: Josin 
 */

#include "tcp_server.h"
#include "../config.h"

int
/*
 * Init the socket with the given host & port, or the following instruction:
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

	printf("before thread_id: %d, t_id: %ld\n", _tid, pthread_self());

	/* Wait signal and wakeup from sleep */
	pthread_cond_wait( &(_thread_cond[_tid]), &(_thread_mutex[_tid]) );

	_list *data = _thread_data[_tid], *head_value = list_first(data);

	int _fd;
	LIST_FOR_EACH_FD(head_value, &_fd){
		if (_fd) {
			printf("file descriptor: %d\n", _fd);
			char *_buff = "HTTP/1.1 200 OK\r\nContent-Type:application/json;charset=utf-8\r\nContent-Length:10\r\n\r\n{\"a\":\"aa\"}";
			write(_fd, _buff, strlen(_buff));
		}
	} LIST_FOR_EACH_END;

	return EMPTY_PTR;
}

void
/*
 * Init the sub-thread with the given thread_number or 0 to use the default number : 2
 * In default: there are only two thread: main thread and only child-thread
 * Main thread do the job assign the newly client to the sub-thread
 * Child thread do tht client's connections from the main thread */
xserver_init_threads(const int thread_number)
{

	for (int i = 0; i < thread_number; ++i) {
		/* Pthread cond. */
		pthread_cond_init( &_thread_cond[i], EMPTY_PTR );

		/* Pthread mutex */
		pthread_mutex_init( &_thread_mutex[i], EMPTY_PTR );

		/* Initialise the _list data */
		_thread_data[i] = init_list();

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

	while ( 1 )
	{
		_client_fd = accept( _sock_fd, (struct sockaddr*)&client_addr, &client_addr_len );
		if ( _client_fd )
		{
			/* Assign the newly client to it's child-thread
			 * After assigning notify the thread to wake it up from sleepy. */
			dispatch_id = _client_fd % _thread_number;

			_list *data = init_list();
			data->_fd = _client_fd;
			data->status = 0;

			printf("new client: %d, dispatch_id: %d\n", _client_fd, dispatch_id);

			/* Add the client fd to the thread_data _list */
			push_back_list(_thread_data[dispatch_id], data);

			/* notify the thread */
			pthread_cond_signal(&_thread_cond[dispatch_id]);
		}
	}
}