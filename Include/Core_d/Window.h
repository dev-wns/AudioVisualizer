#pragma once
#include "StdAfx.hpp"
#include "Singleton.hpp"

class Window : public Singleton<Window>
{
public:
	Window() = default;
	virtual ~Window() = default;

public:
	bool SetWindow( HINSTANCE inst, int width, int height, LPCWSTR className );

public:
	void Run();
	void ResizeClient( UINT width, UINT height );
	void WindowMessageEvent( const MSG& msg );
	LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

private:
	void GameRun();
	virtual void GameInit() { }
	virtual void GameFrame() { }
	virtual void GameRender() { }
	virtual void GameRelease() { }

private:
	HINSTANCE hInstance;
};

