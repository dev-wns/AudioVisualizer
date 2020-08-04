#pragma once
#include "..\\Standard\Singleton.hpp"
#include "..\\Core\DirectX\Device.h"
#include "..\\Core\DirectX\State\DxState.h"
#include "..\\Core\DirectX\RenderTarget\RenderTarget.h"

class DxManager : public Device, public Singleton<DxManager>
{
private:		 DxManager() = default;
public:	virtual ~DxManager() = default;

public:
	void SetRenderTargetView();
	void ResizeClient( UINT width, UINT height );

public:
	bool isState( ERasterizer rsState );
	bool isState( EDepthStencil dsState );
	bool isState( ESampler samState );
	bool isState( EBlend blendState );

	void SetState( ERasterizer rsState );
	void SetState( EDepthStencil dsState );
	void SetState( ESampler samState );
	void SetState( EBlend blendState );

public:
	void SetWindowHandle( const HWND& handle ) { hWnd = handle; }
	const HWND& GetWindowHandle() { return hWnd; }
	RECT& GetClientRect() { return clientRect; }
	RECT& GetWindowRect() { return windowRect; }

public:
	void Init();
	void PreRender();
	void Render();
	void PostRender();
	void Release();

private:
	friend class Singleton<DxManager>;
	DxState state;
	RenderTarget dxRT;
	RECT clientRect;
	RECT windowRect;
	HWND hWnd;
};