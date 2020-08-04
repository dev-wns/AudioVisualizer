#include "StdAfx.hpp"
#include "Core.h"
#include "DxManager.h"
#include "ObjectManager.h"
#include "SoundManager.h"
#include "Timer.h"
#include "Input.h"

void Core::GameInit()
{
	try
	{
		Timer::Get()->Init();
		ObjectManager::Get()->PrevInit();
		DxManager::Get()->Init();
		SoundManager::Get()->Init();
		Init();
		ObjectManager::Get()->PostInit();
	}
	catch( const Exception& ex ) 
	{
		ex.what();
	}
}

void Core::GameFrame()
{
	try
	{
		Timer::Get()->Frame();
		Input::Get()->Frame( DxManager::Get()->GetWindowHandle() );
		
		SoundManager::Get()->Frame();
		Frame();
		ObjectManager::Get()->Frame();
	}
	catch ( const Exception& ex )
	{
		ex.what();
	}
}

void Core::GameRender()
{
	try
	{
		if ( Timer::Get()->IsFixedFrameRate() == true )
		{
			DxManager::Get()->PreRender();
			Render();
			ObjectManager::Get()->Render( DxManager::Get()->GetContext() );
			DxManager::Get()->PostRender();
		}
	}
	catch ( const Exception& ex )
	{
		ex.what();
	}
}

void Core::GameRelease()
{
	Release();
	ObjectManager::Get()->Release();
	SoundManager::Get()->Release();
	TextureManager::Get()->Release();
	DxManager::Get()->Release();
	IOStream::Get()->CloseFile( EIOType::Output );
}