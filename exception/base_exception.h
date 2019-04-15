//
// Created by Josin on 19-4-15.
// Email: xeapplee@gmail.com
// The following code is global exception code in xserver software
// ---begin--
// Code: 10001 --> Invalid HTTP Stream
// Code: 10002 --> Request Method is invalid
// Code: 10003 --> Content-Length is invalid when not in GET method
// Code: 10004 --> HTTP request stream not completed
// ---end---

#ifndef XSERVER_BASE_EXCEPTION_H
#define XSERVER_BASE_EXCEPTION_H

#include <exception>
#include <string>
namespace xserver
{
	class base_exception : public std::exception
	{
		int __code;
		typedef std::string string;
		string __msg;

	public:
		const char *
		what() const noexcept override;

		int
		code() const noexcept;

		base_exception(string &&_msg, int &&_code)
		{
			__msg = _msg;
			__code = _code;
		}

		base_exception(const string &&_msg, const int &&_code)
		{
			__msg = _msg;
			__code = _code;
		}

		void
		setMsg(string &&_msg)
		{
			__msg = _msg;
		}

		void
		setCode(int &&_code)
		{
			__code = _code;
		}
	};
}

#endif // XSERVER_BASE_EXCEPTION_H
