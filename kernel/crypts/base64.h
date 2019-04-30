/**
 * File: ${FILE} for project Xserver
 * Email: xeapplee@gmail.com
 * website: https://www.supjos.cn
 * Author: Josin 
 */

#ifndef XSERVER_BASE64_H
#define XSERVER_BASE64_H

#include "../config.h"

#include <stdlib.h>
#include <string.h>

__BEGIN_DECL

unsigned char *base64_encode(unsigned char *str);

unsigned char *base64_decode(unsigned char *code);

__END_DECL

#endif /* XSERVER_BASE64_H */
