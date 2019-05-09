/**
 * File:{string.h} for project {Xserver}.
 * Author: Josin
 * Email: xeapplee@gmail.com
 * Website: https://www.supjos.cn
 */

#ifndef XSERVER_STRING_H
#define XSERVER_STRING_H

#include "../config.h"

__BEGIN_DECL

#define BUFFER_SIZE 4096

char *
/* Get the substring of the string */
string_substr(const char *src, ssize_t length);

char *
/* Get the substring of the string
 * _mode: 0 -> trim left space
 * _mode: 1 -> trim right space
 * _mode: 2 -> trim both right & left space */
string_substr_option(const char *src, ssize_t length, int _mode);

void
/* This function turn the source string's char case to lowercase */
string_to_lower(char *src);

void
/* Turn the source's string to uppercase */
string_to_upper(char *src);

char *
/* Trim space from the src string
 * mode: 0 -> trim left space
 * mode: 1 -> trim right space
 * mode: 2 -> trim both right & left space */
trim_space(char *src, int _mode);

void
/* Split the string by the delimiter for example:
 * src: hello||world
 * delimiter: ||
 * so first calling result is: result => hello
 * second invoking result is : world
 * This function not allocate memory, developer need keep that the result parameter
 * has memory to store the data */
split_string(const char *_source, const char *delimiter, char *result, int _over);

char *
/* Get the socket stream data from the sock when I/O reading is available
 * Note that: when IO buffer size is 4096, it will let the kernel buffer mostly useful
 * other than more or lower size, and when there is no data for reading, it will let
 * the kernel blocked!!! REMEMBER TO FREE THE RESULT WHEN USED */
get_stream_from_socket(int __sock_fd);

void *
/* To parse the HTTP stream and return the result of the stream
 * The str_len is the parameter which get the result of the current stream end-of tag */
parse_http_stream(const char *http_stream, int *str_len);



__END_DECL

#endif /* XSERVER_STRING_H */
