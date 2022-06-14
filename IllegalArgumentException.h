/**
 * @file IllegalArgumentException.h
 * @author Christopher Liudahl-Rackley and Mohamed Elfergani
 * @brief IllegalArgumentException class
 * @version 0.1
 * @date 2021-11-07
 */

#include <stdexcept>
#include <string>
#ifndef ILLEGAL_ARGUMENT_EXCEPTION
#define ILLEGAL_ARGUMENT_EXCEPTION

class IllegalArgumentException : public std::exception {
	std::string _msg;
public:
	explicit IllegalArgumentException(std::string what) noexcept : _msg{ std::move(what) } {}
	virtual ~IllegalArgumentException() = default;
	virtual char const* what() const noexcept { return _msg.c_str(); }
};

#endif //ILLEGAL_ARGUMENT_EXCEPTION