#include "StdAfx.hpp"
#include "Core.h"
#include "DxManager.h"
#include "ObjectManager.h"
#include "SoundManager.h"
#include <thread>

void Core::GameInit()
{
	ObjectManager::Get()->PrevInit();

	DxManager::Get()->Init();
	Timer::Get()->Init();
	Init();
	ObjectManager::Get()->PostInit();

}


void Core::GameFrame()
{
	Timer::Get()->Frame();
	Input::Get()->Frame( DxManager::Get()->GetWindowHandle() );
	
	SoundManager::Get()->Frame();
	Frame();
	ObjectManager::Get()->Frame();
}

void Core::GameRender()
{
	static float elapseFPSTime( 0.0f );
	elapseFPSTime += Timer::Get()->SPF();

	static DWORD fps ( 0 );
	static float elapseTime ( 0 );
	elapseTime += Timer::Get()->SPF();
	if ( elapseTime > 1.0f )
	{
		std::string debug2( "Core Fixed Frame Rate : " + std::to_string( fps ) + "\n" );
		::OutputDebugStringA( debug2.c_str() );
		fps = 0;
		elapseTime = 0;
	}

	if ( Timer::Get()->IsFixedFrameRate() ) //elapseFPSTime >= 1.0f / 144.0f )
	{
		DxManager::Get()->PreRender();
		Render();
		ObjectManager::Get()->Render( DxManager::Get()->GetContext() );
		DxManager::Get()->PostRender();

		elapseFPSTime = 0.0f;
		fps++;
	}
}

void Core::GameRelease()
{
	Release();
	ObjectManager::Get()->Release();
	//State::Release();
}

//void Core::ResizeClient( UINT width, UINT height )
//{
//	Device::Get()->ResizeClient( GetWindowHandle(), width, height );
//	Window::ResizeClient( width, height );
//}