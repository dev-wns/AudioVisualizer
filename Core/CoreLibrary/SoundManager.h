#pragma once
#include "..\\..\\ExternalLibraries\\FMOD\\include\\fmod.h"
#include "..\\..\\ExternalLibraries\\FMOD\\include\\fmod.hpp"
#pragma comment(lib,"fmodex64L_vc.lib")
//#pragma comment(lib,"fmodex64_vc.lib")
//#pragma comment(lib,"fmodex64p_vc.lib")

#include "Singleton.hpp"

enum class ESoundCount { S64 = 0, S128, S256, S512, S1024, S2048, S4096L, S4096R, S8192L, S8192R };

class SoundManager : public Singleton<SoundManager>
{
public:
	SoundManager();
	virtual ~SoundManager() = default;
	enum class ESound { BackGround = 31, };

public:
	bool LoadSoundFile( const std::string& _path );
	void CreateSoundBuffer();
	const float* GetSpectrum( ESoundCount type ) const;

public:
	bool isPlaying();
	void Play( const std::string& _name );
	void Play();

public:
	//void Play( int iIndex );
	//void Stop( int iIndex );
	//void Paused( int iIndex );
	void AddVolume( float value );

public:
	void Init();
	void Frame();
	void Release();

private:
	FMOD_DSP_FFT_WINDOW type;
	FMOD::System* soundSystem;
	std::map<std::string, FMOD::Sound*> musics;
	FMOD::Sound* currentPlaySound;
	std::map<ESoundCount, float*> spectrum;
	std::vector<FMOD::Channel*> channels;
	float volume;
};

