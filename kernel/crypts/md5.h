/**
 * File: ${FILE} for project Xserver
 * Email: xeapplee@gmail.com
 * website: https://www.supjos.cn
 * Author: Josin 
 */

#ifndef XSERVER_MD5_H
#define XSERVER_MD5_H

#include "../config.h"

__BEGIN_DECL

int32_t
md5(char *result, size_t size, const char *message, uint32_t flag);

__END_DECL

#endif /* XSERVER_MD5_H */
