#pragma once
#include "Exception.hpp"

class RuntimeError : public Exception
{
public:
	explicit RuntimeError( const char* _message = "" ) noexcept : Exception( _message ) { }
	explicit RuntimeError( const std::string _message ) noexcept : Exception( _message ) { }
	virtual ~RuntimeError() = default;

public:
	const char* What() const override
	{
		return GetExceptionMessage().empty() == true ? "runtime error." : Exception::What();
	}
};

class Overflow : public RuntimeError
{
public:
	explicit Overflow( const char* _message = "" ) noexcept : RuntimeError( _message ) { }
	explicit Overflow( const std::string _message ) noexcept : RuntimeError( _message ) { }
	virtual ~Overflow() = default;

public:
	const char* What() const override
	{
		return GetExceptionMessage().empty() == true ? "overflow." : RuntimeError::What();
	}
};

class Underflow : public RuntimeError
{
public:
	explicit Underflow( const char* _message = "" ) noexcept : RuntimeError( _message ) { }
	explicit Underflow( const std::string _message ) noexcept : RuntimeError( _message ) { }
	virtual ~Underflow() = default;

public:
	const char* What() const override
	{
		return GetExceptionMessage().empty() == true ? "underflow." : RuntimeError::What();
	}
};