#pragma once
#include <tchar.h>
// #include <algorithm>

namespace Utility 
{
	#include "..\\..\\..\\..\\ExternalLibraries\\DirectX11\\Include\\d3dx11.h"
	namespace Buffer 
	{
		static ID3D11Buffer* CreateBuffer( D3D11_BIND_FLAG flag, ID3D11Device* device, void* pData, UINT iSize, UINT iNumCount, bool bDynamic = false )
		{
			HRESULT hr( S_OK );
			ID3D11Buffer* pBuffer = 0;
			D3D11_BUFFER_DESC pDesc;
			ZeroMemory( &pDesc, sizeof( D3D11_BUFFER_DESC ) );
			pDesc.ByteWidth = iSize * iNumCount;
			if ( bDynamic )
			{
				pDesc.Usage = D3D11_USAGE_DYNAMIC;
				pDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			}
			else
			{
				pDesc.Usage = D3D11_USAGE_DEFAULT;
				pDesc.CPUAccessFlags = 0;
			}
			pDesc.BindFlags = flag;
			pDesc.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA pInitialData;
			ZeroMemory( &pInitialData, sizeof( D3D11_SUBRESOURCE_DATA ) );
			pInitialData.pSysMem = pData;

			if ( FAILED( hr = device->CreateBuffer( &pDesc, &pInitialData, &pBuffer ) ) )
			{
				return NULL;
			}

			return pBuffer;
		}
	}

	namespace Material 
	{
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

template <typename TYPE>
inline TYPE Minimum( const TYPE& a, const TYPE& b )
{
	return a < b ? a : b;
}

template <typename TYPE>
inline TYPE Maximum( const TYPE& a, const TYPE& b )
{
	return a > b ? a : b;
}

template<typename _Ty>
static void SafeDelete( _Ty*& object )
{
	if ( object == nullptr )
	{
		return;
	}

	delete object;
	object = nullptr;
}

template<typename _Ty>
static void SafeDeleteArray( _Ty*& object )
{
	if ( object == nullptr )
	{
		return;
	}

	delete[] object;
	object = nullptr;
}

template< typename _Ty >
static void SafeRelease( _Ty*& object , bool isDelete = false)
{
	if ( object == nullptr )
	{
		return;
	}

	object->Release();
	if ( isDelete == true ) delete object;
	object = nullptr;
}