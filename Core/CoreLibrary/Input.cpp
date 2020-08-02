#include "Stdafx.hpp"
#include "Input.h"
#include "Device.h"


void Input::WindowMessageEvent( MSG msg )
{
	switch ( msg.message )
	{
		case WM_LBUTTONDOWN:
		{
			mouseState[0] = EKeyState::KEY_PUSH;
		}break;
		case WM_LBUTTONUP:
		{
			mouseState[0] = EKeyState::KEY_UP;
		}break;
		case WM_RBUTTONDOWN:
		{
			mouseState[1] = EKeyState::KEY_PUSH;
		}break;
		case WM_RBUTTONUP:
		{
			mouseState[1] = EKeyState::KEY_UP;
		}break;
		case WM_MBUTTONDOWN:
		{
			mouseState[2] = EKeyState::KEY_PUSH;
		}break;
		case WM_MBUTTONUP:
		{
			mouseState[2] = EKeyState::KEY_UP;
		}break;
	}
}

EKeyState Input::KeyCheck( DWORD dwKey )
{
	SHORT key( GetAsyncKeyState( dwKey ) );
	if ( key & 0x8000 )
	{
		if ( keyState[dwKey] == EKeyState::KEY_FREE || keyState[dwKey] == EKeyState::KEY_UP )
		{
			keyState[dwKey] = EKeyState::KEY_PUSH;
		}
		else
		{
			keyState[dwKey] = EKeyState::KEY_HOLD;
		}
	}
	else
	{
		if ( keyState[dwKey] == EKeyState::KEY_PUSH || keyState[dwKey] == EKeyState::KEY_HOLD )
		{
			keyState[dwKey] = EKeyState::KEY_UP;
		}
		else
		{
			keyState[dwKey] = EKeyState::KEY_FREE;
		}
	}
	return keyState[dwKey];
}

void Input::Frame( HWND hWnd )
{
	::GetCursorPos( &mousePosition );
	::ScreenToClient( hWnd, &mousePosition );
	for ( int buttonCount = 0; buttonCount < 3; buttonCount++ )
	{
		if ( mouseStateBefore[buttonCount] == EKeyState::KEY_PUSH )
		{
			if ( mouseState[buttonCount] == EKeyState::KEY_PUSH )
			{
				mouseState[buttonCount] = EKeyState::KEY_HOLD;
			}
		}

		if ( mouseStateBefore[buttonCount] == EKeyState::KEY_UP )
		{
			if ( mouseState[buttonCount] == EKeyState::KEY_UP )
			{
				mouseState[buttonCount] = EKeyState::KEY_FREE;
			}
		}
		mouseStateBefore[buttonCount] = mouseState[buttonCount];

	}
}
