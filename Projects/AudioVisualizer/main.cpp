#pragma once
#include "Core.h"
#include "DxManager.h"
#include "Plane.h"
#include "ObjectManager.h"
#include "SoundManager.h"
#include "Spectrum.h"
#include "ParticleSystem.h"
#include <thread>
#include "SoundPlayer.h"
#include "Const.h"
#include "TextureManager.h"
//#include "..\\..\\Core\Core.h"
//#include "..\\..\\Core\DxManager.h"
//#include "..\\..\\Include\Core_d\\GameObject.h"

class Sample : public Core
{
	GameObject* spec;
	GameObject* spec1;
	ParticleSystem* part;
	SoundPlayer* m;
public:
	void Init() override
	{
		SoundManager::Get()->Init();
		{
			if ( SoundManager::Get()->LoadSoundFile( "..\\..\\Resource\\Sound\\music33.mp3" ) == false )
				SoundManager::Get()->LoadSoundFile( Path::DefaultSound );
		}
		TextureManager::Get()->AddTexture( Path::DefaultBackgound );

		m = new SoundPlayer( L"Spectrum", ObjectManager::Get()->GetCamera( ECamera::UI ), EObject::UI );
		ObjectManager::Get()->AddObject( m );
	}

	void Frame() override
	{
		if ( SoundManager::Get()->isPlaying() == true 
			 && Input::Get()->KeyCheck( VK_SPACE ) == EKeyState::KEY_PUSH )
		{
			SoundManager::Get()->Play();
		}
	}

	void Render() override
	{
	}

	void Release() override
	{
	}

	Sample() {}
};

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow )
{
	std::cout << lpCmdLine << std::endl;
	std::cout << lpCmdShow << std::endl;
	std::cout << hInstance << std::endl;
	std::cout << hPrevInstance << std::endl;

	Sample core;
	if ( core.SetWindow( hInstance, 2560, 1440, L"Audio Visualizer" ) )
	{
		core.Run();
		return 0;
	}

	return 1;
}