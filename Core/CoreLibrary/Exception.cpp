#include "StdAfx.hpp"
#include "Exception.h"
#include "BaseUtility.hpp"

const char* Exception::What() const
{
	ErrorWrite( message );
	::OutputDebugStringA( message.c_str() );
	return message.empty() == true ? "unknown exception." : message.c_str();
}