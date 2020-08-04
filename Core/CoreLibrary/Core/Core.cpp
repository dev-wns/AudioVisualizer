//#include "..\\Standard\Standard.hpp"
#include "Core.h"
#include "..\\Managed\DxManager.h"
#include "..\\Managed\ObjectManager.h"
#include "..\\Managed\SoundManager.h"
#include "Standard\Timer.h"
#include "Standard\Input.h"

void Core::GameInit()
{
	Timer::Get()->Init();
	ObjectManager::Get()->PrevInit();
	DxManager::Get()->Init();
	SoundManager::Get()->Init();
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
	if ( Timer::Get()->IsFixedFrameRate() == true )
	{
		DxManager::Get()->PreRender();
		Render();
		ObjectManager::Get()->Render( DxManager::Get()->GetContext() );
		DxManager::Get()->PostRender();
	}
}

void Core::GameRelease()
{
	Release();
	ObjectManager::Get()->Release();
	SoundManager::Get()->Release();
	TextureManager::Get()->Release();
	DxManager::Get()->Release();
}