#include <iostream>
#include "kernel/parser.h"
#include "exception/base_exception.h"
#include "kernel/tcp_server.h"

int main()
{
	// std::string request_data = "POST index.php?a=hello&b=world HTTP/1.1\r\n"
	// 						   "Content-Type: application/json;charset=utf-8\r\n"
	// 						   "Status Code: 200 OK\r\n"
	//                            "Content-Length: 11\r\n"
	// 					       "Token: whattokenis\r\n"
	// 	                       "\r\n"
	// 				           "Hello World";
	//
	// xserver_parser parser;
	// xserver_parser::string_size _pos = 0;
	//
	// try {
	// 	std::map<std::string, std::string> values = parser.parse_http_stream(request_data, _pos);
	// 	request_data.erase(0, _pos);
	// 	for (const auto &s : values) {
	// 		std::cout << s.first << ": " << s.second << std::endl;
	// 	}
	// } catch(xserver::base_exception &e) {
	// 	std::cout << e.code() << std::endl;
	// }

	tcp_server server;
	server.run();

	return 0;
}