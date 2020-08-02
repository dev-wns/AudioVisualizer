#pragma once
#include "Singleton.hpp"

enum class EKeyState : char { KEY_FREE = 0,	KEY_PUSH, KEY_UP, KEY_HOLD, };

class Input : public Singleton<Input>
{
private:		 Input() = default;
public: virtual ~Input() = default;

public:
	const POINT& GetMousePosition() const { return mousePosition; }

public:
	void WindowMessageEvent( MSG msg );
	EKeyState KeyCheck( DWORD dwKey );
	void Frame( HWND hWnd );

private:
	friend class Singleton<Input>;
	EKeyState keyState[256];
	EKeyState mouseState[3];
	EKeyState mouseStateBefore[3];
	POINT mousePosition;
};
