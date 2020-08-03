#pragma once
#include "..\\..\\ExternalLibraries\\DirectX11\\Include\\d3dx11.h"
#include <string>

namespace Utility { namespace Material {

namespace Name
{
	const static std::wstring Default( L"..\\..\\Resource\\Shader\\Default.hlsl" );
	const static std::wstring DefaultInstance( L"..\\..\\Resource\\Shader\\Default.fx" );
}

static ID3D11InputLayout* CreateLayout( ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* IED, int ElementCnt, ID3DBlob* pVSBlob )
{
	HRESULT hr( S_OK );
	ID3D11InputLayout* ILOut( 0 );
	DWORD dwSize = ( DWORD )pVSBlob->GetBufferSize();
	LPCVOID dwPoint = pVSBlob->GetBufferPointer();
	if ( FAILED( hr = device->CreateInputLayout( IED, ElementCnt, dwPoint, dwSize, &ILOut ) ) )
	{
		return nullptr;
	}
	return ILOut;
}

static HRESULT CompileShader( const std::wstring& loadFileName, ID3DBlob** pBlob, const std::string& shaderFuncName, const std::string& shaderModel )
{
	HRESULT hr( S_OK );
	ID3DBlob* pErrorBlob( 0 );
	if ( FAILED( hr = D3DX11CompileFromFileW( loadFileName.c_str(), NULL, NULL, shaderFuncName.c_str(), shaderModel.c_str(), 0, 0, NULL, pBlob, &pErrorBlob, NULL ) ) )
	{
		OutputDebugStringA( ( char* )pErrorBlob->GetBufferPointer() );
		return hr;
	}

	return hr;
}

static ID3D11VertexShader* LoadVertexShader( ID3D11Device* device, const std::wstring& szLoadFileName, ID3DBlob** ppBlobOut, const char* szShaderFunc )
{
	HRESULT hr( S_OK );
	ID3DBlob* pBlob( 0 );
	ID3D11VertexShader* VS( 0 );
	if ( szShaderFunc == 0 )
	{
		if ( FAILED( hr = CompileShader( szLoadFileName.c_str(), &pBlob, "VS", "vs_5_0" ) ) )
		{
			return nullptr;
		}
	}
	else
	{
		if ( FAILED( hr = CompileShader( szLoadFileName.c_str(), &pBlob, szShaderFunc, "vs_5_0" ) ) )
		{
			return nullptr;
		}
	}
	DWORD dwSize( 0 );
	LPCVOID lpData( 0 );
	dwSize = ( DWORD )pBlob->GetBufferSize();
	lpData = pBlob->GetBufferPointer();

	if ( FAILED( hr = device->CreateVertexShader( lpData, dwSize, NULL, &VS ) ) )
	{
		pBlob->Release();
		return nullptr;
	}
	if ( ppBlobOut == nullptr )
	{
		pBlob->Release();
		return nullptr;
	}
	else
	{
		*ppBlobOut = pBlob;
	}
	return VS;
}

static ID3D11PixelShader* LoadPixelShader( ID3D11Device* device, const std::wstring& szLoadFileName, ID3DBlob** ppBlobOut, const char* szShaderFunc )
{
	HRESULT hr( S_OK );
	ID3DBlob* pBlob( 0 );
	ID3D11PixelShader* PS( 0 );
	if ( szShaderFunc == 0 )
	{
		if ( FAILED( hr = CompileShader( szLoadFileName.c_str(), &pBlob, "PS", "ps_5_0" ) ) )
		{
			return nullptr;
		}
	}
	else
	{
		if ( FAILED( hr = CompileShader( szLoadFileName.c_str(), &pBlob, szShaderFunc, "ps_5_0" ) ) )
		{
			return nullptr;
		}
	}
	DWORD dwSize( 0 );
	LPCVOID lpData( 0 );
	dwSize = ( DWORD )pBlob->GetBufferSize();
	lpData = pBlob->GetBufferPointer();

	if ( FAILED( hr = device->CreatePixelShader( lpData, dwSize, NULL, &PS ) ) )
	{
		pBlob->Release();
		return nullptr;
	}
	if ( ppBlobOut == nullptr )
	{
		pBlob->Release();
		return nullptr;
	}
	else
	{
		*ppBlobOut = pBlob;
	}
	return PS;
}	
}
}