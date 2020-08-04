#include "Exception.h"
#include "BaseUtility.hpp"

const char* Exception::What() const
{
	ErrorWrite( message );
	return message.empty() == true ? "unknown exception." : message.c_str();
}