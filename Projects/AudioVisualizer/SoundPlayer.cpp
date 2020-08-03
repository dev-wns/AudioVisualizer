#include "StdAfx.hpp"
#include "SoundPlayer.h"
#include "DxManager.h"
#include "Const.h"
#include "Input.h"

void SoundPlayer::Init()
{
	SoundManager::Get()->Init();
	if ( SoundManager::Get()->LoadSoundFile( "..\\..\\Resource\\Sound\\music40.mp3" ) == false )
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

	if ( SoundManager::Get()->isPlaying() == true
		&& Input::Get()->KeyCheck( VK_SPACE ) == EKeyState::KEY_PUSH )
	{
		SoundManager::Get()->Play();
	}
}

void SoundPlayer::Release()
{
	SafeRelease( centerImage );
	SafeRelease( backGround );
	SafeRelease( spectrum );
	SafeRelease( particle );
}

void SoundPlayer::BassUpdate()
{
	const float& spf( Timer::Get()->SPF() );
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

	// ���� �̹��� ũ�� ���� ȿ��
	if ( isCenterBass == true )
	{
		centerImage->GetComponent<Transform>()->SetScale( aroundScale + bassAmount, aroundScale + bassAmount, 1.0f );
		spectrum->UpdatePosition( aroundScale, bassAmount );
	}

	// ī�޶� ���� ȿ�� ( UI Cam )
	if ( isCameraShake == true )
	{
		const float& shakeAmount( rawBassValue * shakePower );
		const float& shakeSin( ::sin( Timer::Get()->GameTimer() * 3.141592f * shakeAmount ) );
		const float& shakeCos( ::cos( Timer::Get()->GameTimer() * 3.141592f * shakeAmount ) );

		Camera* cam( ObjectManager::Get()->GetCamera( ECamera::UI ) );
		cam->GetComponent<Transform>()->Translate( shakeSin, shakeCos, 0.0f );
	}
}