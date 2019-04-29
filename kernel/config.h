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
#include "tools/server_chain.h"
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#ifdef __cplusplus
	#define EMPTY_PTR nullptr
	#define __BEGIN_DECL extern "C" {
	#define __END_DECL };
#else
	#define EMPTY_PTR NULL
	#define __BEGIN_DECL
	#define __END_DECL
#endif

/*
 * All sub-thread max number is 256, if you want to incr it.
 * you should to modify the following parameter */
#define MAX_THREAD_NUMBER 256
pthread_t       _threads[MAX_THREAD_NUMBER];
pthread_mutex_t _thread_mutex[MAX_THREAD_NUMBER];
pthread_cond_t  _thread_cond[MAX_THREAD_NUMBER];
_list          *_thread_data[MAX_THREAD_NUMBER];
int             _thread_id[MAX_THREAD_NUMBER];
int             _thread_number;

#endif /* XSERVER_CONFIG_H */
