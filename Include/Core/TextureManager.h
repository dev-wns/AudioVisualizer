#pragma once
#include <map>
#include "Texture.h"
#include "Singleton.hpp"

class TextureManager : public Singleton<TextureManager>
{
private:	     TextureManager() = default;
public:	virtual ~TextureManager() = default;

public:
	Texture* GetTexture( const std::wstring& _name )
	{
		const auto& oneTextureIter = textures.find( _name );
		if ( oneTextureIter == std::end( textures ) )
		{
			throw;
		}

		Texture* retData( oneTextureIter->second );
		return retData;
	}

	void PushTexture( const std::wstring& _path )
	{
		if ( _path.empty() == true )
		{
			throw;
		}

		Texture* oneTexture( new Texture() );
		oneTexture->NameDivide( _path.c_str() );

		if ( textures.find( oneTexture->GetName() ) != std::end( textures ) )
		{
			SafeRelease( oneTexture );
		}

		oneTexture->CreateShaderResourceView( _path );
		textures.insert( std::make_pair( oneTexture->GetName(), oneTexture ) );
	}

	void PopTexture( )//const std::wstring& _name )
	{

	}

	void Release()
	{
		for ( auto& oneTexture : textures )
		{
			SafeRelease( oneTexture.second );
		}

		// Texture��ü ���� SRV�� ����.
		// map�� Texture��ü �����
	}

private:
	// name, texture
	friend class Singleton<TextureManager>;
	std::map<std::wstring, Texture*> textures;
};

