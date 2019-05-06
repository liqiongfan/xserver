/**
 * File: config.h for project Xserver
 * Email: xeapplee@gmail.com
 * Website: https://www.supjos.cn
 * Author: Josin 
 */

#ifndef XSERVER_CONFIG_H
#define XSERVER_CONFIG_H

/* Default buffer key size */
#define KEY_BUFFER_SIZE 256
#define BUCKET_SIZE 5000

#ifdef __cplusplus
#define EMPTY_PTR nullptr
	#define __BEGIN_DECL extern "C" {
	#define __END_DECL };
#else
    #define EMPTY_PTR NULL
    #define __BEGIN_DECL
    #define __END_DECL
    #define true  1
    #define false 0
#endif

#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include "tools/list.h"
#ifdef __linux__
#include <sys/epoll.h>
#endif

/* The debug mode, when in production set DEBUG to 0 otherwise 1 */
#define DEBUG true

/* Notice:
 * This typedef macro defines the extension so library callback
 * kernel will parse the http request stream into list map, for developer to use.
 * request_headers contains the http request server info, and query_string_list contains
 * the query string if exists or null if empty. */
typedef char *(*HTTP_FUNC)(struct _list *request_headers, struct _list *query_string_list);

/* Some macros for LOG print.
 * default log level is INFO_LEVEL, This level is the most widely common used level,
 * kernel will output every log info to stdout */
#define LOG_ERROR_LEVEL 1
#define LOG_WARN_LEVEL  2
#define LOG_INFO_LEVEL  3
#if DEBUG
#define LOG_INFO(level, msg, ...) \
    if ( level <= LOG_INFO_LEVEL ) { \
        printf(msg, __VA_ARGS__); }
#else
#define LOG_INFO(level, msg, ...)
#endif

/* Some macros for type defines */
typedef unsigned int  uint;
typedef unsigned long ulong;
typedef unsigned char uchar;

/* All sub-thread max number is 256, if you want to incr it.
 * you should to modify the following parameter */
#define MAX_THREAD_NUMBER 256
pthread_t       _threads[MAX_THREAD_NUMBER];
pthread_mutex_t _thread_mutex[MAX_THREAD_NUMBER];
pthread_cond_t  _thread_cond[MAX_THREAD_NUMBER];
#ifdef __linux__
int             _thread_data[MAX_THREAD_NUMBER];
#endif
int             _thread_id[MAX_THREAD_NUMBER];
int             _thread_number;

#endif /* XSERVER_CONFIG_H */
