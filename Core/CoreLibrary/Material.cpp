#include "StdAfx.hpp"
#include "Material.h"
#include "DxManager.h"
#include "BaseUtility.hpp"
#include "BaseConst.hpp"

Material::Material() : color( Vector4::Zero ) { }

void Material::SetPixel(const std::string& _name)
{
	pixelShader = Utility::Material::LoadPixelShader( DxManager::Get()->GetDevice(), Shader::Name::Default, &blobPS, _name.c_str() );
}

void Material::SetVertexShader( const std::string& _name )
{
	vertexShader = Utility::Material::LoadVertexShader( DxManager::Get()->GetDevice(), Shader::Name::Default, &blobVS, _name.c_str() );
}

void Material::Init()
{
	vertexShader = Utility::Material::LoadVertexShader( DxManager::Get()->GetDevice(), Shader::Name::Default, &blobVS, "VS" );
	if ( pixelShader == nullptr )
		pixelShader  = Utility::Material::LoadPixelShader( DxManager::Get()->GetDevice(), Shader::Name::Default, &blobPS, "PS" );

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
	if ( vertexShader == nullptr || pixelShader == nullptr || layout == nullptr )
		throw NullPointer( __FUNCTION__" - one of vertex, index shader and layout is null reference.\n" );

	if ( texture != nullptr )
		DxManager::Get()->GetContext()->PSSetShaderResources( 0, 1, &texture->GetResource() );

	DxManager::Get()->GetContext()->IASetInputLayout( layout );
	DxManager::Get()->GetContext()->VSSetShader( vertexShader, NULL, 0 );
	DxManager::Get()->GetContext()->PSSetShader( pixelShader, NULL, 0 );
}

void Material::Release()
{
	SafeRelease( texture );
	SafeRelease( layout );
	SafeRelease( vertexShader );
	SafeRelease( pixelShader );
	SafeRelease( blobVS );
	SafeRelease( blobPS );
}

void  Material::SetTexture( Texture* tx )
{
	if ( tx != nullptr )
		texture = tx;
}
void  Material::SetInstanceLayout()
{
	SafeRelease( vertexShader );
	vertexShader = Utility::Material::LoadVertexShader( DxManager::Get()->GetDevice(), Shader::Name::Default, &blobVS, "VS_INSTANCE" );
	
	SafeRelease( pixelShader );
	pixelShader = Utility::Material::LoadPixelShader( DxManager::Get()->GetDevice(), Shader::Name::Default, &blobPS, "PS_INSTANCE" );

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

void Material::SetColor( const D3DXVECTOR4& _color )
{
	color = _color;
}

void Material::SetColor( const float& r, const float& g, const float& b, const float a )
{
	color.x = r;
	color.y = g;
	color.z = b;
	color.w = a;
}