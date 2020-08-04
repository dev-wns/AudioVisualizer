#pragma once
#include "StdAfx.hpp"

class Exception : public std::exception
{
public:
	explicit Exception( const char* _message = "" ) : message( _message ) { }
	explicit Exception( const std::string& _message ) : message( _message ) { }
	virtual ~Exception() = default;

public:
	virtual const char* What() const;

protected:
	const std::string& GetExceptionMessage() const { return message; }

private:
	std::string message;
};

class LogicError : public Exception
{
public:
	explicit LogicError( const char* _message = "" ) noexcept : Exception( _message ) { }
	explicit LogicError( const std::string _message ) noexcept : Exception( _message ) { }
	virtual ~LogicError() = default;

public:
	const char* What() const override
	{
		return GetExceptionMessage().empty() == true ? "logic error." : Exception::What();
	}
};

class OutOfRange : public LogicError
{
public:
	explicit OutOfRange( const char* _message = "" ) noexcept : LogicError( _message ) { }
	explicit OutOfRange( const std::string _message ) noexcept : LogicError( _message ) { }
	virtual ~OutOfRange() = default;

public:
	const char* What() const override
	{
		return GetExceptionMessage().empty() == true ? "out of range." : LogicError::What();
	}
};

class InvalidArgument : public LogicError
{
public:
	explicit InvalidArgument( const char* _message = "" ) noexcept : LogicError( _message ) { }
	explicit InvalidArgument( const std::string _message ) noexcept : LogicError( _message ) { }
	virtual ~InvalidArgument() = default;

public:
	const char* What() const override
	{
		return GetExceptionMessage().empty() == true ? "invalid argument." : LogicError::What();
	}
};

class EmptyData : public InvalidArgument
{
public:
	explicit EmptyData( const std::string _message ) noexcept : InvalidArgument( "empty data : " + _message ) { }
	virtual ~EmptyData() = default;

public:
	const char* What() const override
	{
		return GetExceptionMessage().empty() == true ? "empty data" : LogicError::What();
	}
};

class NullPointer : public InvalidArgument
{
public:
	explicit NullPointer( const char* _message = "" ) noexcept : InvalidArgument( _message ) { }
	explicit NullPointer( const std::string _message ) noexcept : InvalidArgument( "this object null reference.\n" + _message ) { }
	virtual ~NullPointer() = default;

public:
	const char* What() const override
	{
		return GetExceptionMessage().empty() == true ? "this object null reference.\n" : LogicError::What();
	}
};

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