#include "StdAfx.hpp"
#include "Window.h"
#include "Input.h"
#include "DxManager.h"

LRESULT CALLBACK WndProc( HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam )
{
	return Window::Get()->MsgProc( windowHandle, msg, wParam, lParam );
}

LRESULT Window::MsgProc( HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
		case WM_SIZE:
		{
			if ( wParam != SIZE_MINIMIZED )
			{
				UINT width( LOWORD( lParam ) );
				UINT height( HIWORD( lParam ) );
				ResizeClient( width, height );
			}
		}break;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			::BeginPaint( windowHandle, &ps );
			::EndPaint( windowHandle, &ps );
		}break;

		case WM_DESTROY:
		{
			::PostQuitMessage( 0 );
		}break;

		default: break;
	}

	return ::DefWindowProc( windowHandle, msg, wParam, lParam );
}

void Window::WindowMessageEvent( const MSG& msg )
{
	Input::Get()->WindowMessageEvent( msg );
}

void Window::ResizeClient( UINT width, UINT height )
{
	if( DxManager::Get()->GetWindowHandle() != nullptr )
		DxManager::Get()->ResizeClient( width, height );
}

void Window::Run()
{
	GameInit();
	MSG msg = { 0, };
	while ( Input::Get()->KeyCheck( VK_ESCAPE ) == EKeyState::KEY_FREE )
	{
		if ( ::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			::TranslateMessage( &msg );
			::DispatchMessage( &msg );
			if ( msg.message == WM_QUIT )
			{
				break;
			}
			WindowMessageEvent( msg );
		}
		else
		{
			GameRun();
		}
	}

	GameRelease();
}
bool Window::SetWindow( HINSTANCE inst, int width, int height, LPCWSTR className )
{
	hInstance = inst;

	WNDCLASSEX wc;
	wc.cbSize = sizeof( WNDCLASSEX );
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = ::LoadIcon( hInstance, IDI_ERROR );
	wc.hCursor = ::LoadCursor( hInstance, IDC_IBEAM );
	wc.hbrBackground = static_cast<HBRUSH>( ::GetStockObject( BLACK_BRUSH ) );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className;
	wc.hIconSm = ::LoadIcon( hInstance, IDI_ERROR );
	if ( ::RegisterClassEx( &wc ) == false )
	{
		return false;
	}

	RECT window = { 0, 0, width, height };
	AdjustWindowRect( &window, WS_OVERLAPPEDWINDOW, FALSE );
	//hWnd = ::CreateWindowEx( WS_EX_APPWINDOW, className, className, WS_OVERLAPPEDWINDOW, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL, hInstance, NULL );
	DxManager::Get()->SetWindowHandle( ::CreateWindowEx( WS_EX_APPWINDOW, className, className, WS_OVERLAPPEDWINDOW, 0, 0, window.right - window.left, window.bottom - window.top, NULL, NULL, hInstance, NULL ) );
	if ( DxManager::Get()->GetWindowHandle() == NULL )
	{
		return false;
	}

	RECT& clientRect( DxManager::Get()->GetClientRect() );
	RECT& windowRect( DxManager::Get()->GetWindowRect() );
	const HWND& windowHandle( DxManager::Get()->GetWindowHandle() );

	::GetWindowRect( windowHandle, &windowRect );
	::GetClientRect( windowHandle, &clientRect );

	// 윈도우 창 센터 맞추기.
	const int& screenWidth ( ::GetSystemMetrics( SM_CXSCREEN ) );
	const int& screenHeight( ::GetSystemMetrics( SM_CYSCREEN ) );

	const int& x( ( screenWidth  - ( clientRect.right -  clientRect.left ) ) / 2 );
	const int& y( ( screenHeight - ( clientRect.bottom - clientRect.top ) ) / 2 );

	RECT rt = { 0, 0, clientRect.right, clientRect.bottom };
	::AdjustWindowRect( &rt, GetWindowStyle( windowHandle ), FALSE );
	::MoveWindow( windowHandle, x, y, rt.right - rt.left, rt.bottom - rt.top, true );

	::UpdateWindow( windowHandle );
	::ShowWindow( windowHandle, SW_SHOW );

	return true;
}

void Window::GameRun()
{
	GameFrame();
	GameRender();
}