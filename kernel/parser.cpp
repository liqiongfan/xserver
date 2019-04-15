//
// Created by Josin on 19-4-15.
// Email: xeapplee@gmail.com
//

#include "parser.h"
#include <iostream>
#include <string>
#include <cstring>
#include "../exception/base_exception.h"

xserver_parser::map_values
// This method parse the request or response data, for request data with the following form type:
// First line: GET index.php HTTP/1.1(\r\n or \n)
xserver_parser::parse_http_stream(xserver_parser::string &data, string_size &_after_data_pos)
{
	string _key;
	string_size i, _line_i = 0, _count = 0, _colon_i = 0;

	// Parse the first line data
	for (i = 0; i < data.size(); ++i) {
		// The current char in the http stream
		char _char = data.at(i);
		if ( _char == '\r' && data.at(i + 1) == '\n' ) {
			// if meet the last \n char, it means the previous char-sequence is HTTP version
			headers.insert({"http_version", data.substr(_line_i, i - _line_i)});
			// After used, to reset it to 0 for the next use
			_line_i = i + 2;
			break;
		}

		// if not \n char, to parse the space char
		if ( _char == ' ' ) {
			switch( _count ) {
				case 0:
					_key = "request_method";
					break;
				case 1:
					_key = "request_url";
					break;
				default:
					throw xserver::base_exception("xserver: http stream invalid.", 10001);
			}
			// Add the header key & value into headers
			headers.insert({_key, data.substr(_line_i, i - _line_i)});
			// Set the current pos into value i
			_line_i = i + 1;
			// Incr the count
			++_count;
		}
	}

	// To let the next char to i
	++i;

	// Parse the http stream headers
	// Line 2 to last() - 1:
	// Content-Type: application/json;charset=UTF-8(\r\n or \n)
	for (; i < data.size(); ++i)
	{
		char _char = data.at(i);
		if ( _char == '\r' && data.at(i + 1) == '\n' ) {

			if ( data.at(i + 2) != '\r' && data.at(i + 3) != '\n' ) {
				string_size _j = _colon_i + 1;
				char _nchar = data.at(_j);
				while (_nchar == ' ') {
					_nchar = data.at(++_j);
				}
				_key = data.substr(_line_i, _colon_i - _line_i);
				_tolower(_key);
				headers.insert({
	               _key,
	               data.substr(_j, i - _j)
               });
				_colon_i = 0;
				_line_i = i + 2;
			} else if ( data.at(i + 2) == '\r' && data.at(i + 3) == '\n' )
			{
				i = i + 4;
				break;
			}
		}

		// if meet the ":" to set the _colon_i pos.
		if ( _char == ':' )
			_colon_i = i;
	}

	// Get the request method
	_key = headers["request_method"];
	if ( _key.empty() ) {
		throw xserver::base_exception("Request Method is invalid", 10002);
	}
	// Get the content-length
	long int content_length = std::strtol(headers["content-length"].c_str(), nullptr, 10);
	if ( !content_length && strncasecmp(_key.c_str(), "get", 3) != 0 ) {
		throw xserver::base_exception("Content-Length is invalid when not in GET method", 10003);
	}

	// Set the body into the request body
	_key = data.substr(i, (unsigned long)content_length);
	if ( _key.size() != content_length) {
		throw xserver::base_exception("HTTP request stream not completed", 10004);
	}
	_after_data_pos = i + content_length;
	headers.insert({ "request_body", _key });

	// Return the headers
	return headers;
}
