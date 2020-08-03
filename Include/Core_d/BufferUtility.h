#pragma once
#include "..\\..\\ExternalLibraries\\DirectX11\\Include\\d3dx11.h"

namespace Utility { namespace Buffer {

		static ID3D11Buffer* CreateBuffer( D3D11_BIND_FLAG flag, ID3D11Device* device, void* pData, UINT iSize, UINT iNumCount, bool bDynamic = false )
		{
			HRESULT hr ( S_OK );
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
}