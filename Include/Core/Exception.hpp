#pragma once
#include "StdAfx.hpp"

class Exception : public std::exception
{
public:
	explicit Exception( const char* _message ) : message( _message ) { }
	explicit Exception( const std::string& _message ) : message( _message ) { }
	virtual ~Exception() = default;

public:
	virtual const char* What() const
	{
		return message.empty() == true ? "Unknown Exception." : message.c_str();
	}

protected:
	const std::string& GetExceptionMessage() const { return message; }

private:
	std::string message;
};