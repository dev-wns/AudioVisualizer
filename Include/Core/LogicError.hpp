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
		return GetExceptionMessage().empty() == true ? "Logic Error." : Exception::What();
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
		return GetExceptionMessage().empty() == true ? "Out Of Range." : LogicError::What();
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
		return GetExceptionMessage().empty() == true ? "Invalid Argument." : LogicError::What();
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
		return GetExceptionMessage().empty() == true ? "Empty Data" : LogicError::What();
	}
};	

class EmptyObject : public LogicError
{
public:
	explicit EmptyObject( const char* _message ) noexcept : LogicError( _message ) { }
	explicit EmptyObject( const std::string _message ) noexcept : LogicError( _message ) { }
	virtual ~EmptyObject() = default;

public:
	const char* What() const override
	{
		return GetExceptionMessage().empty() == true ? "Invalid Argument." : LogicError::What();
	}
};