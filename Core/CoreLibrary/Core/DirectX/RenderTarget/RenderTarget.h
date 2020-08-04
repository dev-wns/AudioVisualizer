#pragma once
#include "..\\..\\..\\Standard\Standard.hpp"

class RenderTarget
{
public:
	RenderTarget();
	virtual ~RenderTarget() = default;

public:
	void	ViewPortSet( FLOAT TopLeftX, FLOAT TopLeftY, FLOAT fWidth, FLOAT fHeight );
	HRESULT UpdateDepthStencilView( ID3D11Device* pDevice, FLOAT dwWidth, FLOAT dwHeight );

public:
	void	Apply( ID3D11DeviceContext* d3dContext, ID3D11RenderTargetView* pRTV, ID3D11DepthStencilView* pDepthStencilView, bool bDepth = true, bool bStencil = true );
	bool	Begin( ID3D11DeviceContext* d3dContext, D3DXVECTOR4 vColor, bool bTarget = true, bool bDepth = true, bool bStencil = true );
	bool	End( ID3D11DeviceContext* d3dContext );
	bool	Clear( ID3D11DeviceContext* d3dContext, D3DXVECTOR4 vColor, bool bTarget = true, bool bDepth = true, bool bStencil = true );

public:
	HRESULT	Create( ID3D11Device* d3dDevice, FLOAT fWidth = 1024, FLOAT fHeight = 1024, ID3D11Texture2D* pTex = NULL );
	void	Release();

public:
	ID3D11RenderTargetView*& GetRTView() { return curRTView; }

private:
	ID3D11RenderTargetView*	curRTView;
	ID3D11DepthStencilView*	curDSView;
	ID3D11RenderTargetView* oldRTView;
	ID3D11DepthStencilView*	oldDSView;
	ID3D11ShaderResourceView* resRTV;
	ID3D11ShaderResourceView* resDSV;
	D3D11_DEPTH_STENCIL_VIEW_DESC descDepthStencil;
	D3D11_VIEWPORT curViewPort;
	D3D11_VIEWPORT oldViewPort;
	UINT countViewPort;
};