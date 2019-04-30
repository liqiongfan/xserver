/**
 * File: ${FILE} for project Xserver
 * Email: xeapplee@gmail.com
 * website: https://www.supjos.cn
 * Author: Josin 
 */

#ifndef XSERVER_CONFIG_H
#define XSERVER_CONFIG_H

#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#ifdef __linux__
#include <sys/epoll.h>
#endif

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

/* The debug mode, when in production set DEBUG to 0 otherwise 1 */
#define DEBUG true

typedef char *(*FUNC)();

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

/* All sub-thread max number is 256, if you want to incr it.
 * you should to modify the following parameter */
#define MAX_THREAD_NUMBER 256
pthread_t       _threads[MAX_THREAD_NUMBER];
pthread_mutex_t _thread_mutex[MAX_THREAD_NUMBER];
pthread_cond_t  _thread_cond[MAX_THREAD_NUMBER];
#ifdef __linux__
int             _thread_data[MAX_THREAD_NUMBER];
#else
_list          *_thread_data[MAX_THREAD_NUMBER];
#endif
int             _thread_id[MAX_THREAD_NUMBER];
int             _thread_number;

#endif /* XSERVER_CONFIG_H */
