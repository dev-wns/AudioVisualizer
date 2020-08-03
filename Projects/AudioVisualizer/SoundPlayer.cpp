#include "StdAfx.hpp"
#include "SoundPlayer.h"
#include "DxManager.h"
#include "ObjectManager.h"
#include "SoundManager.h"
#include "Const.h"
#include "Input.h"
#include "Timer.h"

SoundPlayer::SoundPlayer() : 
	bBackGroundVisible( true ), bCenterImageVisible( true ),
	bCameraShake( false ), bCenterBass( true ), bBarBass( true ), 
	aroundScale( 175.0f ), lengthAmount( 2000.0f ),
	bassPower( 25.0f ), bassAmount( 0.0f ), rawBassValue( 0.0f ),
	shakePower( 5.0f ) { }

void SoundPlayer::Init()
{
	Timer::Get()->SetFixedFrameRate( 240 );

	SoundManager::Get()->Init();
	if ( SoundManager::Get()->LoadSoundFile( "..\\..\\Resource\\Sound\\music66.mp3" ) == false )
	 	 SoundManager::Get()->LoadSoundFile( Path::DefaultSound );


	TextureManager::Get()->AddTexture( Path::DefaultBackgound );

	backGround = new Plane( L"BackGround", ObjectManager::Get()->GetCamera( ECamera::UI ), EObject::UI );
	backGround->GetComponent<Transform>()->SetScale( 1440.0f, 1440.0f, 1.0f );
	backGround->GetComponent<Transform>()->SetPosition( 0.0f, 0.0f, 999.0f );
	backGround->GetComponent<Mesh>()->GetVSCB().color = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 0.125f );
	backGround->GetComponent<Material>()->SetTexture( TextureManager::Get()->GetTexture( L"back.jpg" ) );
	backGround->GetComponent<Material>()->SetPixel( "PixelShaderTexture" );
	ObjectManager::Get()->AddObject( backGround );

	particle = new ParticleSystem( L"Particle", ObjectManager::Get()->GetCamera( ECamera::Main ), EObject::UI, 128 );
	ObjectManager::Get()->AddObject( particle );

	spectrum = new Spectrum( L"Spectrum", ObjectManager::Get()->GetCamera( ECamera::UI ), EObject::UI, 90 );
	ObjectManager::Get()->AddObject( spectrum );

	centerImage = new Plane( L"CenterImage", ObjectManager::Get()->GetCamera( ECamera::UI ), EObject::UI );
	centerImage->GetComponent<Transform>()->SetScale( aroundScale, aroundScale, 1.0f );
	centerImage->GetComponent<Material>()->SetPixel( "PS_Sphere" );
	centerImage->GetComponent<Material>()->SetTexture( TextureManager::Get()->GetTexture( L"back.jpg" ) );
	ObjectManager::Get()->AddObject( centerImage );
}

void SoundPlayer::Frame()
{
	Update();

	if ( SoundManager::Get()->isPlaying() == true && 
		 Input::Get()->KeyCheck( VK_SPACE ) == EKeyState::KEY_PUSH )
	{
		SoundManager::Get()->Play();
	}
	
	// 이미지 렌더링 여부
	if ( Input::Get()->KeyCheck( VK_F1 ) == EKeyState::KEY_PUSH )
	{
		bBackGroundVisible = !bBackGroundVisible;
		backGround->SetVisible( bBackGroundVisible );
	}
	if ( Input::Get()->KeyCheck( VK_F2 ) == EKeyState::KEY_PUSH )
	{
		bCenterImageVisible = !bCenterImageVisible;
		centerImage->SetVisible( bCenterImageVisible );
	}

	// 스펙트럼, 센터 이미지의 기준이 되는 원 크기 조절
	if ( Input::Get()->KeyCheck( VK_F3 ) == EKeyState::KEY_HOLD )
	{
		aroundScale += 100.0f * Timer::Get()->GetSPF();
	}
	if ( Input::Get()->KeyCheck( VK_F4 ) == EKeyState::KEY_HOLD )
	{
		aroundScale -= 100.0f * Timer::Get()->GetSPF();
		if ( aroundScale < 0.0f )
			 aroundScale = 0.0f;
	}

	// 스펙트럼 바 길이 조절
	if ( Input::Get()->KeyCheck( VK_F5 ) == EKeyState::KEY_HOLD )
	{
		lengthAmount += 2000.0f * Timer::Get()->GetSPF();
	}
	if ( Input::Get()->KeyCheck( VK_F6 ) == EKeyState::KEY_HOLD )
	{
		lengthAmount -= 2000.0f * Timer::Get()->GetSPF();
		if ( lengthAmount < 0.0f )
			 lengthAmount = 0.0f;
	}

	// 베이스 파워 조절
	if ( Input::Get()->KeyCheck( VK_F7 ) == EKeyState::KEY_HOLD )
	{
		bassPower += 100.0f * Timer::Get()->GetSPF();
	}
	if ( Input::Get()->KeyCheck( VK_F8 ) == EKeyState::KEY_HOLD )
	{
		bassPower -= 100.0f * Timer::Get()->GetSPF();
		if ( bassPower < 0.0f )
	 		 bassPower = 0.0f;
	}
}

void SoundPlayer::Release()
{
	// ObjectManager에서 제거
	//SafeRelease( centerImage );
	//SafeRelease( backGround );
	//SafeRelease( spectrum );
	//SafeRelease( particle );
}

void SoundPlayer::BassUpdate()
{
	const float& spf( Timer::Get()->GetSPF() );
	const float* spec( SoundManager::Get()->GetSpectrum()[ESoundCount::S4096L] );
	float calcValue = 0.0f;

	for ( int count = 0; count < 20; count++ )
	{
		calcValue += spec[count];
	}
	rawBassValue = calcValue;
	calcValue *= bassPower;

	if ( bassAmount < calcValue )
		bassAmount = calcValue;

	if ( bassAmount > 0.0f )
		bassAmount -= 500.0f * spf;
	else
		bassAmount = 0.0f;
}

void SoundPlayer::Update()
{
	BassUpdate();
	spectrum->UpdateLength( lengthAmount );

	// 센터 이미지 크기 조절 효과
	if ( bCenterBass == true )
	{
		centerImage->GetComponent<Transform>()->SetScale( aroundScale + bassAmount, aroundScale + bassAmount, 1.0f );
		spectrum->UpdatePosition( aroundScale, bassAmount );
	}

	// 카메라 흔들기 효과 ( UI Cam )
	if ( bCameraShake == true )
	{
		const float& shakeAmount( rawBassValue * shakePower );
		const float& shakeSin( ::sin( Timer::Get()->GetProgressTime() * 3.141592f * shakeAmount ) );
		const float& shakeCos( ::cos( Timer::Get()->GetProgressTime() * 3.141592f * shakeAmount ) );

		Camera* cam( ObjectManager::Get()->GetCamera( ECamera::UI ) );
		cam->GetComponent<Transform>()->Translate( shakeSin, shakeCos, 0.0f );
	}
}