#pragma once
#include "Exception.hpp"

class LogicError : public Exception
{
public:
	explicit LogicError( const char* _message ) noexcept : Exception( _message ) { }
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
	explicit OutOfRange( const char* _message ) noexcept : LogicError( _message ) { }
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
	explicit InvalidArgument( const char* _message ) noexcept : LogicError( _message ) { }
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
	explicit EmptyData( const char* _message ) noexcept : InvalidArgument( _message ) { }
	explicit EmptyData( const std::string _message ) noexcept : InvalidArgument( _message ) { }
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
	explicit NullPointer( const char* _message ) noexcept : InvalidArgument( _message ) { }
	explicit NullPointer( const std::string _message ) noexcept : InvalidArgument( _message ) { }
	virtual ~NullPointer() = default;

public:
	const char* What() const override
	{
		return GetExceptionMessage().empty() == true ? "this object null reference." : LogicError::What();
	}
};