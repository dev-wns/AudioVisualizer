#include "StdAfx.hpp"
#include "TextureManager.h"
#include "BaseUtility.hpp"

Texture* TextureManager::GetTexture( const std::wstring& _name )
{
	
	const std::map<std::wstring, Texture*>::const_iterator& iter( std::find( std::cbegin( textures ), std::cend( textures ), _name ) );
	if ( iter == std::end( textures ) )
	{
		throw;
	}

	Texture* retData( iter->second );
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

	const std::map<std::wstring, Texture*>::const_iterator& iter( std::find( std::cbegin( textures ), std::cend( textures ), oneTexture->GetName() ) );
	if ( iter != std::cend( textures ) )
	{
		SafeRelease( oneTexture, true );
	}

	oneTexture->CreateShaderResourceView( _path );
	textures.insert( std::make_pair( oneTexture->GetName(), oneTexture ) );
}

void TextureManager::RemoveTexture( const std::wstring& _name )
{
	if ( _name.empty() == true ) return;

	std::map<std::wstring, Texture*>::iterator iter( std::find( std::begin( textures ), std::end( textures ), _name );
	if ( iter == std::end( textures ) ) return;

	SafeRelease( iter->second );
	textures.erase( iter );
}

void TextureManager::Release()
{
	for ( std::map<std::wstring, Texture*>::iterator iter = std::begin( textures );
		  iter != std::end( textures ); iter++ )
	{
		SafeRelease( iter->second, true );
	}
	textures.clear();
}