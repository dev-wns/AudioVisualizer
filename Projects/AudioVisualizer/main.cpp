#pragma once
#include "Core.h"
#include "DxManager.h"
#include "Plane.h"
#include "ObjectManager.h"
#include "SoundManager.h"
#include "Spectrum.h"
#include "ParticleSystem.h"
#include <thread>
#include "MusicPlayer.h"
//#include "..\\..\\Core\Core.h"
//#include "..\\..\\Core\DxManager.h"
//#include "..\\..\\Include\Core_d\\GameObject.h"

class Sample : public Core
{
	GameObject* spec;
	GameObject* spec1;
	ParticleSystem* part;
	MusicPlayer* m;
public:
	void Init() override
	{
		SoundManager::Get()->Init();
		{
			SoundManager::Get()->LoadSoundFile( "..\\..\\Resource\\Sound\\music.mp3" );
		}
		//std::thread t1( [] ()
		//{
		//	SoundManager::Get()->Init();
		//	{
		//		SoundManager::Get()->LoadSoundFile( "..\\..\\Resource\\Sound\\music64.mp3" );
		//		//SoundManager::Get()->LoadSoundFile( "..\\..\\Resource\\Sound\\music31.mp3" );
		//		//SoundManager::Get()->LoadSoundFile( "..\\..\\Resource\\Sound\\music32.mp3" );
		//		//SoundManager::Get()->LoadSoundFile( "..\\..\\Resource\\Sound\\music25.mp3" );
		//		//SoundManager::Get()->LoadSoundFile( "..\\..\\Resource\\Sound\\music20.mp3" );
		//		//SoundManager::Get()->LoadSoundFile( "..\\..\\Resource\\Sound\\music17.mp3" );
		//		//SoundManager::Get()->Play( "music10.mp3" );
		//	} 
		//} );
		//t1.detach();
		TextureManager::Get()->PushTexture( L"..\\..\\Resource\\back.jpg" );

		m = new MusicPlayer( L"Spectrum", ObjectManager::Get()->GetCamera( ECamera::UI ), EObject::UI );
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