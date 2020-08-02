#include "StdAfx.hpp"
#include "Material.h"
#include "ShaderUtility.h"
#include "DxManager.h"

void Material::SetPixel(const std::string& _name)
{
	pixelShader = Utility::Material::LoadPixelShader( DxManager::Get()->GetDevice(), Utility::Material::Name::Default, &blobPS, _name.c_str() );
}

void Material::SetVertexShader( const std::string& _name )
{
	vertexShader = Utility::Material::LoadVertexShader( DxManager::Get()->GetDevice(), Utility::Material::Name::Default, &blobVS, _name.c_str() );
}

void Material::Init()
{
	vertexShader = Utility::Material::LoadVertexShader( DxManager::Get()->GetDevice(), Utility::Material::Name::Default, &blobVS, "VS" );
	if ( pixelShader == nullptr )
		pixelShader  = Utility::Material::LoadPixelShader( DxManager::Get()->GetDevice(), Utility::Material::Name::Default, &blobPS, "PS" );

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	layout = Utility::Material::CreateLayout( DxManager::Get()->GetDevice(), ied, sizeof( ied ) / sizeof( ied[0] ), blobVS );
}

void Material::PrevRender()
{
	if ( vertexShader == nullptr || pixelShader == nullptr || layout == nullptr ) return;

	if ( texture != nullptr )
		DxManager::Get()->GetContext()->PSSetShaderResources( 0, 1, &texture->GetResource() );

	DxManager::Get()->GetContext()->IASetInputLayout( layout );
	DxManager::Get()->GetContext()->VSSetShader( vertexShader, NULL, 0 );
	DxManager::Get()->GetContext()->PSSetShader( pixelShader, NULL, 0 );
}

void Material::Release()
{
	SafeRelease( vertexShader );
	SafeRelease( pixelShader );
	SafeRelease( layout );
	SafeRelease( blobVS );
}

void  Material::SetTexture( Texture* tx )
{
	if ( tx != nullptr )
		texture = tx;
}
void  Material::SetInstanceLayout()
{
	SafeRelease( vertexShader );
	vertexShader = Utility::Material::LoadVertexShader( DxManager::Get()->GetDevice(), Utility::Material::Name::Default, &blobVS, "VS_INSTANCE" );
	
	SafeRelease( pixelShader );
	pixelShader = Utility::Material::LoadPixelShader( DxManager::Get()->GetDevice(), Utility::Material::Name::Default, &blobPS, "PS_INSTANCE" );

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		{ "TRANSFORM", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,    1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "TRANSFORM", 1, DXGI_FORMAT_R32G32B32A32_FLOAT,    1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "TRANSFORM", 2, DXGI_FORMAT_R32G32B32A32_FLOAT,    1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "TRANSFORM", 3, DXGI_FORMAT_R32G32B32A32_FLOAT,    1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "POSCOLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,    1, 64, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	};

	SafeRelease( layout );
	layout = Utility::Material::CreateLayout( DxManager::Get()->GetDevice(), ied, sizeof( ied ) / sizeof( ied[0] ), blobVS );
}