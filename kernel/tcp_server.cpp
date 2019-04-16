//
// Created by Josin on 19-4-16.
// Email: xeapplee@gmail.com
//

#include "tcp_server.h"
#include <thread>
#include <cerrno>
#include <vector>

void
// Accept any client socket connections and assign each client socket into different thread to do the socket job.
// response to the client socket
tcp_server::run()
{
	// client_fd store the client fd
	int client_fd;

	// client sock data
	sockaddr_in client_addr{};
	bzero(&client_addr, sizeof(client_addr));
	socklen_t client_socklen;

	// All threads
	auto *ids = new std::thread[_sub_thread_num];

	// start several thread as sub-thread
	for (int i = 0; i < _sub_thread_num; ++i) {
		// Create the threads
		ids[i] = std::thread(&tcp_server::_thread_server, this, i);
		// Let the thread to mutex
		// if you want to resume from the mutex status
		// set the `_thread_status[i] = 1`
		_thread_status.insert({i, 0});
	}

	int _assign_thread_id = 0;
	while( true ) {
		client_fd = accept(_socket_fd, (sockaddr *)&client_addr, &client_socklen);

		if ( client_fd ) {
			// Arriving new client connection, pick it from the thread stores
			// assign to some of the thread
			incr_all_socket_number();

			// Assign the client_fd to the sub-thread
			_assign_thread_id = (client_fd % _sub_thread_num);

			add_client_to_thread( _assign_thread_id, client_fd );
			set_thread_start(_assign_thread_id);
			bzero(&client_addr, sizeof(client_addr));
		}
	}

	// When running to the end of the main thread, sleep to let the sub-thread end.
	for (int j = 0; j < _sub_thread_num; ++j) ids[j].join();
	delete[] ids;
}
