#include "StdAfx.hpp"
#include "DxManager.h"
#include "ObjectManager.h"

void DxManager::SetRenderTargetView()
{
	if ( GetSwapChain() == nullptr ) return;

	DXGI_SWAP_CHAIN_DESC SwapDesc = { 0, };
	GetSwapChain()->GetDesc( &SwapDesc );
	ID3D11Texture2D* pResource( nullptr );
	if ( GetSwapChain()->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pResource ) == E_FAIL
		|| dxRT.Create( GetDevice(), ( FLOAT )SwapDesc.BufferDesc.Width, ( FLOAT )SwapDesc.BufferDesc.Height, pResource ) == E_FAIL )
	{
		throw;
	}
}

void DxManager::ResizeClient( UINT width, UINT height )
{
	if ( d3dContext == nullptr ) return;
	d3dContext->OMSetRenderTargets( 0, nullptr, nullptr );

	SafeRelease( swapChain );
	CreateSwapChain( hWnd, width, height );

	ID3D11RenderTargetView*& rtv( dxRT.GetRTView() );
	SafeRelease( rtv );
	SetRenderTargetView();

	for ( std::pair<ECamera, Camera*> oneCamera : ObjectManager::Get()->GetCameras() )
	{
		oneCamera.second->CreateProjMatrix( width, height );
	}

	clientRect.right = width;
	clientRect.bottom = height;

	::GetClientRect( hWnd, &clientRect );
	::GetWindowRect( hWnd, &windowRect );
}


bool DxManager::isState( ERasterizer rsState )
{
	return state.raster[rsState] == nullptr ? false : true;
}

bool DxManager::isState( EDepthStencil dsState )
{
	return state.depth[dsState] == nullptr ? false : true;
}

bool DxManager::isState( ESampler samState )
{
	return state.sampler[samState] == nullptr ? false : true;
}

bool DxManager::isState( EBlend blendState )
{
	return state.blend[blendState] == nullptr ? false : true;
}

void DxManager::SetState( ERasterizer rsState )
{
	if ( state.raster[rsState] == nullptr ) return;
	GetContext()->RSSetState( state.raster[rsState] );
}

void DxManager::SetState( EDepthStencil dsState )
{
	if ( state.depth[dsState] == nullptr ) return;
	GetContext()->OMSetDepthStencilState( state.depth[dsState], 0x00 );
}

void DxManager::SetState( ESampler samState )
{
	if ( state.sampler[samState] == nullptr ) return;
	GetContext()->PSSetSamplers( 0, 1, &state.sampler[samState] );
}

void DxManager::SetState( EBlend blendState )
{
	if ( state.blend[blendState] == nullptr ) return;
	GetContext()->OMSetBlendState( state.blend[blendState], 0, 0xffffffff );
}

void DxManager::Init()
{
	Device::Init( hWnd, clientRect.right, clientRect.bottom );
	state.Init( GetDevice() );
	DxManager::Get()->SetState( ESampler::Clamp );
	DxManager::Get()->SetState( ERasterizer::None );
	DxManager::Get()->SetState( EBlend::Alpha );
	DxManager::Get()->SetState( EDepthStencil::Enable );

	SetRenderTargetView();
}
void DxManager::PreRender()
{
	dxRT.Begin( GetContext(), Color::Black, true, true, true );
	GetContext()->IASetPrimitiveTopology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
}

void DxManager::Render()
{
	PreRender();
	PostRender();
}

void DxManager::PostRender()
{
	dxRT.End( GetContext() );
	GetSwapChain()->Present( 0, 0 );
}

void DxManager::Release()
{
	Device::Release();
	state.Release();
	dxRT.Release();
}