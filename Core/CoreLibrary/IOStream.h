#pragma once
#include "StdAfx.hpp"
#include <fstream>
#include "Singleton.hpp"

enum class EIOType : char
{
	Input = 0,
	Output,
};

class IOStream : public Singleton<IOStream>
{
public:
	IOStream() = default;
	virtual ~IOStream();

public:
	const std::string& GetReadData() const;
	std::ifstream& GetInputStream();

public:
	bool IsOpen( EIOType type );

public:
	void OpenFile( const std::string& path, EIOType type );
	void CloseFile( EIOType type );
	void Read();
	void Write( const std::string& data, bool IsIndent = false );

private:
	void CreateNewFile( const std::string& path );

private:
	std::ifstream inputStream;
	std::ofstream outputStream;
	std::string readData;
};