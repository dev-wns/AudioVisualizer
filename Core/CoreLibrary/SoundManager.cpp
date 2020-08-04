#include "StdAfx.hpp"
#include "SoundManager.h"
#include "Timer.h"
#include "BaseUtility.hpp"

bool SoundManager::isPlaying()
{
	bool isPlay( true );
	return channels[0]->isPlaying( &isPlay );
}

std::map<ESoundCount, float*>& SoundManager::GetSpectrum()
{
	return spectrum;
}

bool SoundManager::LoadSoundFile( const std::string& _path )
{
	if ( _path.empty() == true ) 
		throw EmptyData( __FUNCTION__" - argument empty.\n" );

	// 사운드 생성
	FMOD::Sound* sound( nullptr );
	if ( soundSystem->createSound( _path.c_str(), FMOD_DEFAULT, 0, &sound ) != FMOD_RESULT::FMOD_OK ) 
		throw LogicError( __FUNCTION__" - soundSystem create failed.\n" );
	// path에서 이름만 자르기
	std::string name;
	const size_t& pos( _path.find_last_of( L'\\' ) );

	if ( pos == std::string::npos )
	{
		throw OutOfRange( __FUNCTION__" - the end of the string has been reached.\n" );
	}

	for ( size_t start = pos + 1; start != _path.size(); start++ )
	{
		name.push_back( _path[start] );
	}
	musics.insert( std::make_pair( name, sound ) );

	return true;
}

void SoundManager::Play()
{
	if ( std::cbegin( musics )->second == nullptr ) 
		throw NullPointer( __FUNCTION__" - the first data in the music is null reference.\n" );

	bool isPlay( false );
	for ( FMOD::Channel* oneChannel : channels )
	{
		if ( oneChannel->isPlaying( &isPlay ) == FMOD_RESULT::FMOD_OK || oneChannel == nullptr )
		{
			soundSystem->playSound( FMOD_CHANNELINDEX::FMOD_CHANNEL_FREE, std::cbegin( musics )->second, false, &channels[0] );

			currentPlaySound = std::cbegin( musics )->second;
			channels[0]->setVolume( 1.0f );
			break;
		}
	}
}

void SoundManager::Play( const std::string& _name )
{
	if ( _name.empty() == true || musics.find( _name ) == std::end( musics ) ) 
		throw EmptyData( __FUNCTION__" - argument data is empty or failed to find music.\n" );

	bool isPlay( false );
	for ( FMOD::Channel* oneChannel : channels )
	{
		if ( oneChannel->isPlaying( &isPlay ) == FMOD_RESULT::FMOD_OK || oneChannel == nullptr )
		{
			soundSystem->playSound( FMOD_CHANNELINDEX::FMOD_CHANNEL_FREE, musics[_name], false, &channels[0] );

			currentPlaySound = musics[_name];
			break;
		}
	}
}

//void SoundManager::Play( int iIndex )
//{
//	bool playing = false;
//	if ( iIndex == 2 )
//	{
//		int i = 2;
//		while ( 1 )
//		{
//			if ( m_pChannel[i]->isPlaying( &playing ) )
//			{
//				m_pSystem->playSound( m_pSound[iIndex], 0, false, &m_pChannel[i] );
//				break;
//			}
//			if ( i < 32 ) i++;
//		}
//	}
//	else
//	{
//		if ( m_pChannel[iIndex] != NULL )
//			m_pChannel[iIndex]->isPlaying( &playing );
//		if ( playing == false )
//		{
//			m_pSystem->playSound( m_pSound[iIndex], 0, false, &m_pChannel[iIndex] );
//		}
//	}
//}
//void SoundManager::Stop( int iIndex )
//{
//	bool playing = false;
//	if ( m_pChannel != NULL )
//		m_pChannel[iIndex]->isPlaying( &playing );
//	if ( playing == false )
//	{
//		m_pSystem->playSound( m_pSound[iIndex], 0, false, &m_pChannel[iIndex] );
//		float m_fCurrentVolume;
//		m_fCurrentVolume = 0.1f;
//		m_pChannel[iIndex]->setVolume( m_fCurrentVolume );
//	}
//	else
//		m_pChannel[iIndex]->stop();
//}
//void Paused( int iIndex )
//{
//	bool paused;
//	m_pChannel[iIndex]->getPaused( &paused );
//	m_pChannel[iIndex]->setPaused( !paused );
//}
void SoundManager::AddVolume( float value )
{
	channels[0]->getVolume( &volume );
	const float& compareValue( volume + value );

	if ( compareValue <= 0.0f || compareValue >= 1.0f ) 
		throw OutOfRange( __FUNCTION__" - the sound volume must be between 0 ~ 1.\n" );

	volume += value;
	channels[0]->setVolume( volume );
}

void SoundManager::CreateSoundBuffer()
{
	//if ( recordSound != nullptr )
	//	recordSound->release();
	//FMOD_RESULT hr;
	//static int const channelCount = 2;
	FMOD_CREATESOUNDEXINFO soundInfo;
	::memset( &soundInfo, 0, sizeof( FMOD_CREATESOUNDEXINFO ) );

	soundInfo.cbsize = sizeof( FMOD_CREATESOUNDEXINFO );
	soundInfo.numchannels = 1;
	soundInfo.format = FMOD_SOUND_FORMAT_PCMFLOAT;
	soundInfo.defaultfrequency = 44100;
	soundInfo.length = soundInfo.defaultfrequency * sizeof( short ) * soundInfo.numchannels;


	// hr = soundSystem->createSound( 0, FMOD_2D | FMOD_OUTPUTTYPE_WINMM | FMOD_OPENUSER, &soundInfo, &recordSound );
	//hr = soundSystem->createSound( 0, FMOD_SOFTWARE | FMOD_OUTPUTTYPE_WINMM | FMOD_OPENUSER, &soundInfo, &recordSound );
	//recordSound->setMode( FMOD_LOOP_NORMAL );
}

void SoundManager::Init()
{
	//CreateSoundBuffer();
	//spectrum.insert( std::make_pair( ESoundCount::S64, new float[64] ) );
	//spectrum.insert( std::make_pair( ESoundCount::S128, new float[128] ) );
	//spectrum.insert( std::make_pair( ESoundCount::S256, new float[256] ) );
	//spectrum.insert( std::make_pair( ESoundCount::S1024, new float[1024] ) );
	//spectrum.insert( std::make_pair( ESoundCount::S2048, new float[2048] ) );
	//spectrum.insert( std::make_pair( ESoundCount::S8192L, new float[8192] ) );
	//spectrum.insert( std::make_pair( ESoundCount::S8192R, new float[8192] ) );
	spectrum.insert( std::make_pair( ESoundCount::S512, new float[512] ) );
	spectrum.insert( std::make_pair( ESoundCount::S4096L, new float[4096] ) );
	spectrum.insert( std::make_pair( ESoundCount::S4096R, new float[4096] ) );

	channels.resize( 32 );

	FMOD_RESULT fr( FMOD_OK );
	if ( ( fr = FMOD::System_Create( &soundSystem ) ) != FMOD_OK ) return;
	if ( ( fr = soundSystem->init( 32, FMOD_INIT_NORMAL, 0 ) ) != FMOD_OK ) return;
	//fr = soundSystem->setOutput( FMOD_OUTPUTTYPE_WINMM );


	//static int const channelCount = 2;
	//FMOD_CREATESOUNDEXINFO soundInfo;
	//memset( &soundInfo, 0, sizeof( FMOD_CREATESOUNDEXINFO ) );

	//soundInfo.cbsize = sizeof( FMOD_CREATESOUNDEXINFO );
	//soundInfo.numchannels = 1;
	//soundInfo.format = FMOD_SOUND_FORMAT_PCMFLOAT;
	//soundInfo.defaultfrequency = 44100;
	//soundInfo.length = soundInfo.defaultfrequency * sizeof( short ) * soundInfo.numchannels;
	//fr = soundSystem->createSound( 0, FMOD_2D | FMOD_OPENUSER, &soundInfo, &recordSound );

	//CreateSoundBuffer();
	//FMOD::Channel* recordChannel;
	//fr = soundSystem->setDriver( 0 );
	//fr = soundSystem->playSound( FMOD_CHANNEL_FREE, recordSound, false, &recordChannel );

	//std::thread t1( [&] ()
	//{
	//	while ( true )
	//	{
	//		//soundSystem->getSpectrum( spectrum[ESoundCount::S64], 64, 0, FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS );
	//		//soundSystem->getSpectrum( spectrum[ESoundCount::S128], 128, 0, FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS );
	//		//soundSystem->getSpectrum( spectrum[ESoundCount::S256], 256, 0, FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS );
	//		//soundSystem->getSpectrum( spectrum[ESoundCount::S1024], 1024, 0, FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS );
	//		//soundSystem->getSpectrum( spectrum[ESoundCount::S2048], 2048, 0, FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS );

	//		soundSystem->getSpectrum( spectrum[ESoundCount::S512], 512, 0, FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS );
	//		soundSystem->getSpectrum( spectrum[ESoundCount::S4096L], 4096, 0, FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS );
	//		soundSystem->getSpectrum( spectrum[ESoundCount::S4096R], 4096, 1, FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS );

	//		//soundSystem->getSpectrum( spectrum[ESoundCount::S8192L], 8192, 0, FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS );
	//		//soundSystem->getSpectrum( spectrum[ESoundCount::S8192R], 8192, 1, FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS );
	//		//Sleep( 10 );
	//	}
	//} );
	//t1.detach();
}

void SoundManager::Frame()
{
	if ( Timer::Get()->IsFixedFrameRate() == true )
	{
		soundSystem->getSpectrum( spectrum[ESoundCount::S512], 512, 0, FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS );
		soundSystem->getSpectrum( spectrum[ESoundCount::S4096L], 4096, 0, FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS );
		soundSystem->getSpectrum( spectrum[ESoundCount::S4096R], 4096, 1, FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS );
	}
	soundSystem->update();
}

void SoundManager::Release()
{
	// 공식 FMOD 문서에 채널은 Release 할 필요가 없다고 하고, Release 메서드 자체가 없음.
	for ( std::vector<FMOD::Channel*>::iterator iter = std::begin( channels );
		  iter != std::end( channels ); iter++ )
	{
		( *iter )->stop();
	}

	for ( std::map<std::string, FMOD::Sound*>::iterator it = std::begin( musics ); it != std::end( musics ); it++ )
	{
		if ( it->second == nullptr ) continue;

		it->second->release();
		it->second = nullptr;
	}
	musics.clear();

	for ( std::map<ESoundCount, float*>::iterator it = std::begin( spectrum ); it != std::end( spectrum ); it++	)
	{
		SafeDeleteArray( it->second );
	}
	spectrum.clear();

	if ( soundSystem != nullptr )
	{
		soundSystem->close();
		soundSystem->release();
		soundSystem = nullptr;
	}
}