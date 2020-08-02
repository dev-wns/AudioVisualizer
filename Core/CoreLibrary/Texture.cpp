#include "StdAfx.hpp"
#include "Texture.h"
#include "DxManager.h"

void Texture::CreateShaderResourceView( const std::wstring& _path )
{
	HRESULT hr = S_OK;
	if ( FAILED( hr = D3DX11CreateShaderResourceViewFromFile( DxManager::Get()->GetDevice(), _path.c_str(), NULL, NULL, &resource, NULL ) ) )
	{
		return;
	}
	NameDivide( _path.c_str() );
	path = _path;
}

void Texture::Release()
{
	SafeRelease( resource );
}

void Texture::NameDivide( const std::wstring& _path )
{
	size_t pos( _path.find_last_of( L'\\' ) );
	if ( pos == std::wstring::npos )
	{
		throw;
	}

	if ( name.empty() == false )
	{
		name.clear();
	}

	for ( size_t start = pos + 1; start != _path.size(); start++ )
	{
		name.push_back( _path[start] );
	}
}