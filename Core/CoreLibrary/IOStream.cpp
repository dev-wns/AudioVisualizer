#include "IOStream.h"

IOStream::~IOStream()
{
	if ( inputStream.is_open() == true )
	{
		inputStream.close();
	}
	if ( outputStream.is_open() == true )
	{
		outputStream.close();
	}
}

const std::string& IOStream::GetReadData() const
{
	return readData;
}

std::ifstream& IOStream::GetInputStream()
{
	return inputStream;
}

bool IOStream::IsOpen( EIOType type )
{
	if ( type == EIOType::Input )
		return inputStream.is_open();

	return outputStream.is_open();
}

void IOStream::OpenFile( const std::string& path, EIOType type )
{
	if ( type == EIOType::Input )
	{
		inputStream.open( path, std::ios::in );

		if ( inputStream.is_open() == false )
		{
			CreateNewFile( path );
			inputStream.open( path, std::ios::in );
		}

		return;
	}

	outputStream.open( path, std::ios::out | std::ios::trunc );

	if ( outputStream.is_open() == false )
	{
		throw LogicError( __FUNCTION__" - the output stream could not be opened.\n" );
	}
}

void IOStream::CloseFile( EIOType type )
{
	if ( type == EIOType::Input )
	{
		if ( inputStream.is_open() == true )
		{
			inputStream.close();

			return;
		}
	}

	if ( outputStream.is_open() == true )
	{
		outputStream.close();
	}
}

void IOStream::Read()
{
	if ( inputStream.is_open() == false )
	{
		return;
	}

	inputStream.seekg( 0, std::ios::end );
	int fileFullSize = static_cast< int >( inputStream.tellg() );
	readData.resize( fileFullSize );
	inputStream.seekg( 0, std::ios::beg );
	inputStream.read( &readData[0], fileFullSize );

	size_t pos( readData.find_first_of( "\n" ) );
	while ( pos != std::string::npos )
	{
		readData.insert( pos, "\r" );
		pos = readData.find_first_of( "\n", pos + 2 );
	}
}

void IOStream::Write( const std::string& data, bool IsIndent )
{
	if ( data.empty() == true )
	{
		return;
	}

	if ( outputStream.is_open() == false )
	{
		throw LogicError( __FUNCTION__" - the output stream could not be opened.\n" );
	}

	if ( IsIndent == false )
	{
		outputStream << data;

		return;
	}

	outputStream << data << std::endl;
}

void IOStream::CreateNewFile( const std::string& path )
{
	std::ifstream newFile( path, std::ios::out | std::ios::trunc );
	newFile.close();
}