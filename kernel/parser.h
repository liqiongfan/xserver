//
// Created by Josin on 19-4-15.
// Email: xeapplee@gmail.com
//

#ifndef XSERVER_PARSER_H
#define XSERVER_PARSER_H

#include <string>
#include <strings.h>
#include <map>

class xserver_parser
{
	// The following types will be used int kernel to do the parsing job.
	typedef std::string string;
	typedef std::map<string,string> map_values;

	// The values means the value need to be store into.
	map_values headers;

public:
	// Command used type for the string size or outer space to define the string size
	typedef std::string::size_type string_size;

	/**
	 * To turn the source string into lower case
	 * @param string source The source string and result string
	 */
	void _tolower(string &source)
	{
		for (char &i : source) {
			i = (char)std::tolower(i);
		}
	}

	/**
	 * This function will parse the http request stream and return the std::map<string, string> data
	 * with the second function parameter _after_data_pos: to let programmer to get the next starting position.
	 * @param string data The request http stream the system to parse from
	 * @param _after_data_pos position to the next parsing job start.
	 * @return std::map<string, string> containing all http request raw data
	 */
	map_values parse_http_stream(string &data, string_size &_after_data_pos);

};

#endif // XSERVER_PARSER_H
