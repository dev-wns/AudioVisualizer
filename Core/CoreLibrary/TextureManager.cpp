#include "StdAfx.hpp"
#include "TextureManager.h"

Texture* TextureManager::GetTexture( const std::wstring& _name )
{
	const auto& oneTextureIter = textures.find( _name );
	if ( oneTextureIter == std::end( textures ) )
	{
		throw;
	}

	Texture* retData( oneTextureIter->second );
	return retData;
}

void TextureManager::AddTexture( const std::wstring& _path )
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

void TextureManager::RemoveTexture( const std::wstring& _name )
{
	if ( _name.empty() == true ) return;

	std::map<std::wstring, Texture*>::iterator iter( textures.find( _name ) );
	if ( iter == std::end( textures ) ) return;

	SafeRelease( iter->second );
	textures.erase( iter );
}

void TextureManager::Release()
{
	for ( auto& oneTexture : textures )
	{
		SafeRelease( oneTexture.second );
	}

	// Texture객체 안의 SRV는 지움.
	// map의 Texture객체 지우기
}