#include "StdAfx.hpp"
#include "TextureManager.h"
#include "BaseUtility.hpp"

Texture* TextureManager::GetTexture( const std::wstring& _name )
{
	const std::map<std::wstring, Texture*>::const_iterator& iter( textures.find( _name ) );

	if ( iter == std::cend( textures ) ) 
		throw EmptyData( __FUNCTION__" - the textures iterator has reached the end.\n" );

	return iter->second;
}

void TextureManager::AddTexture( const std::wstring& _path )
{
	if ( _path.empty() == true ) 
		throw EmptyData( __FUNCTION__" - the textures iterator has reached the end.\n" ); 

	Texture* oneTexture( new Texture() );
	oneTexture->NameDivide( _path.c_str() );

	const std::map<std::wstring, Texture*>::const_iterator& iter( textures.find( oneTexture->GetName() ) );
	if ( iter != std::cend( textures ) )
	{
		SafeRelease( oneTexture, true );
	}

	oneTexture->CreateShaderResourceView( _path );
	textures.insert( std::make_pair( oneTexture->GetName(), oneTexture ) );
}

void TextureManager::RemoveTexture( const std::wstring& _name )
{
	if ( _name.empty() == true ) 
		throw EmptyData( __FUNCTION__" - argument empty.\n" );

	std::map<std::wstring, Texture*>::iterator iter( textures.find( _name ) );
	if ( iter == std::end( textures ) ) 
		throw EmptyData( __FUNCTION__" - the textures iterator has reached the end.\n" );

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