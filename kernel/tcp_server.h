//
// Created by Josin on 19-4-16.
// Email: xeapplee@gmail.com
//

#ifndef XSERVER_TCP_SERVER_H
#define XSERVER_TCP_SERVER_H

#include <string>
#include <cassert>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <arpa/inet.h>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <map>
#include <list>
#include <cstring>

class tcp_server
{
	// Some types used inline
	typedef std::string string;
	typedef std::map<int, int> map_data;
	typedef std::map<int, std::list<int>> map_vector;

	// Some values & properties
	int _socket_fd;
	long long _all_socket_number = 0;
	int _sub_thread_num = 5;
	sockaddr_in _server_addr;

	// Conditional Variables & all datas
	std::condition_variable cv;
	std::mutex mutex;
	map_data _thread_status;
	map_vector _thread_jobs;


public:
	/**
	 * To initialise the socket with the given host & port
	 * @param string host The host addr you want to creat the socket
	 * @param int port The port the socket server listen to
	 */
	tcp_server(const string &host = "0.0.0.0", const int &port = 8181, const int &_backlog = 100)
	{
		int result;

		// Create the socket
		_socket_fd = socket( AF_INET, SOCK_STREAM, 0);
		assert(_socket_fd != -1);

		int opt = SO_REUSEADDR;
		setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

		// Clear the addr info.
		bzero(&_server_addr, sizeof(_server_addr));
		_server_addr.sin_port = htons((uint16_t) port);
		_server_addr.sin_family = AF_INET;
		_server_addr.sin_addr.s_addr = inet_addr(host.c_str());
		result = bind(_socket_fd, (const sockaddr *)&_server_addr, sizeof(_server_addr));
		assert(result != -1);

		// Listen the socket
		result = listen(_socket_fd, _backlog);
		assert(result != -1);
	}

	/**
	 * To set the thread number with the given parameter _number(default is 5)
	 * @param int _number
	 * @return true or false will occur the assert failed
	 */
	inline bool
	set_thread_number(int _number)
	{
		assert(_number > 0);
		_sub_thread_num = _number;
		return true;
	}

	/**
	 * Set the socket val with the _opt_name & _opt_val to do the realise modify job.
	 * @param int    _opt_name   The option name for the socket to set
	 * @param void * _opt_val    The option value for the socket to set
	 * @return true or false will be terminated by assert
	 */
	inline bool
	set_socket_opt(int _opt_name, void *_opt_val)
	{
		int result = setsockopt(_socket_fd, SOL_SOCKET, _opt_name, _opt_val, sizeof(int));
		assert(result != -1);
		return true;
	}

	/**
	 * Get the socket val with the _opt_name & _opt_val with the system invoked to `getsockopt`
	 * @param int    _opt_name The sock name
	 * @param void * _opt_val  The buffer to store the value(need to be turned to void *)
	 * @return true or false will occur the assert failed.
	 */
	inline bool
	get_socket_opt(int _opt_name, void *_opt_val)
	{
		socklen_t opt_len = sizeof(int);
		int result = getsockopt(_socket_fd, SOL_SOCKET, _opt_name, _opt_val, &opt_len);
		assert(result != -1);
		return true;
	}

	// Run the tcp_server with the initialise socket info.
	// This is in the main thread, after each client socket arrived, main thread will assign each client to
	// the sub-thread to deal the data and support concurrency
	// The sub(child)-thread number can be modified by `setThreadCounts(10)` function
	void run();

	// Add client_id to the `_thread_job` list with the given _thread_id & _client_id
	inline void
	add_client_to_thread(int _thread_id, int _client_id)
	{
		_thread_jobs[_thread_id].push_back(_client_id);
	}

	// Each calling to the function will let the kernel to
	inline int
	get_client_job(int _thread_id)
	{
		int client_id = _thread_jobs[_thread_id].front();
		_thread_jobs[_thread_id].pop_front();
		return client_id;
	}

	// Get the all socket number
	inline long long
	get_all_socket_number()
	{
		return _all_socket_number;
	}

	// This function must be called by main thread, any sub-thread
	// mustn't call the function
	inline void
	incr_all_socket_number()
	{
		_all_socket_number++;
	}

	// Set the thread status resume from the wait status
	// To start to deal the job.
	inline void
	set_thread_start(int _thread_id)
	{
		_thread_status[_thread_id] = 1;
		cv.notify_all();
	}

	// This function will be ran each time when kernel notify it
	// Child thread will running util
	inline void
	_thread_server(int pid)
	{
		while (true) {
			// Wait until the thread status ok
			std::unique_lock<std::mutex> _thread(mutex);
			cv.wait(_thread, [&] {
				return _thread_status[pid];
			});

			int client_id = get_client_job(pid);
			std::cout << pid << ":" << client_id << std::endl;
			const char *buffer = "HTTP/1.1 200 OK\r\nContent-Type:application/json;charset=utf-8\r\nContent-Length:22\r\n\r\n{\"name\":\"hello world\"}";
			write(client_id, buffer, std::strlen(buffer));
			close(client_id);
			_thread_status[pid] = 0;
			_thread.unlock();
		}
	}
};

#endif // XSERVER_TCP_SERVER_H
