#pragma once
#include "RenderTarget.h"

class Device
{
protected:	     Device() = default;
public:	virtual ~Device() = default;

public:
	void ResizeClient( const HWND& hWnd, UINT width, UINT height );
	ID3D11Device* GetDevice() { return d3dDevice; }
	ID3D11DeviceContext* GetContext() { return d3dContext; }
	IDXGISwapChain* GetSwapChain() { return swapChain; }

public:
	void Init( const HWND& hWnd, UINT width, UINT height );
	//void PreRender();
	//void Render();
	//void PostRender();
	void Release();

private:
	HRESULT	CreateFactory();
	HRESULT	CreateDevice();
	HRESULT	CreateSwapChain( const HWND& hWnd, UINT width, UINT height );
	//HRESULT	SetRenderTargetView();

private:
	friend class DxManager;

private:
	ID3D11Device* d3dDevice;
	ID3D11DeviceContext* d3dContext;
	IDXGISwapChain* swapChain;
	IDXGIFactory* dxgiFaxtory;
	//RenderTarget renderTarget;
};

