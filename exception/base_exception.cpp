//
// Created by Josin on 19-4-15.
// Email: xeapplee@gmail.com
//

#include "base_exception.h"

const char *
xserver::base_exception::what() const noexcept
{
	return __msg.c_str();
}

int
xserver::base_exception::code() const noexcept
{
	return __code;
}
