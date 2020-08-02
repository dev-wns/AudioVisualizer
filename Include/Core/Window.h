#pragma once
#include "StdAfx.hpp"
#include "Singleton.hpp"

class Window : public Singleton<Window>
{
public:
	Window();
	virtual ~Window();

public:
	//const HWND& GetWindowHandle() { return hWnd; }
	//const RECT& GetClientRect() const { return clientRect; }
	//const RECT& GetWindowRect() const { return windowRect; }
	bool SetWindow( HINSTANCE inst, int width, int height, LPCWSTR className );

public:
	void Run();
	void ResizeClient( UINT width, UINT height );
	void WindowMessageEvent( const MSG& msg );
	LRESULT MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

private:
	void GameRun()
	{
		GameFrame();
		GameRender();
	}
	virtual void GameInit() { }
	virtual void GameFrame() { }
	virtual void GameRender() { }
	virtual void GameRelease() { }
private:
	HINSTANCE hInstance;
	//HWND hWnd;
	//RECT windowRect;
	//RECT clientRect;
};

