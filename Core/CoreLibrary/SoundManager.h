#pragma once
#include "..\\..\\ExternalLibraries\\FMOD\\include\\fmod.h"
#include "..\\..\\ExternalLibraries\\FMOD\\include\\fmod.hpp"
#include <thread>
//#pragma comment(lib,"fmodex64_vc.lib")
#pragma comment(lib,"fmodex64L_vc.lib")
//#pragma comment(lib,"fmodex64p_vc.lib")

#include "Singleton.hpp"

enum class ESoundCount { S64 = 0, S128, S256, S512, S1024, S2048, S4096L, S4096R, S8192L, S8192R };
class SoundManager : public Singleton<SoundManager>
{
public:
	SoundManager() = default;
	virtual ~SoundManager() = default;
	enum class ESound { BackGround = 31, };

public:
	bool LoadSoundFile( const std::string& _path );
	void CreateSoundBuffer();
	std::map<ESoundCount, float*>& GetSpectrum();

public:
	bool isPlaying();
	void Play( const std::string& _name );
	void Play();

public:
	//void Play( int iIndex );
	//void Stop( int iIndex );
	//void Paused( int iIndex );
	//void Volume( int iIndex, bool bUp );

public:
	void Init();
	void Frame();
	void Release();

private:
	FMOD::System* soundSystem;
	std::map<std::string, FMOD::Sound*> musics;
	std::map<ESoundCount, float*> spectrum;
	std::vector<FMOD::Channel*> channels;

public:
	static float maxSptValue;
};

