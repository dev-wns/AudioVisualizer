#include "StdAfx.hpp"
#include "SoundPlayer.h"
#include "DxManager.h"

void SoundPlayer::Init()
{
	spectrum = new Spectrum( L"Spectrum", ObjectManager::Get()->GetCamera( ECamera::UI ), EObject::UI, 90 );
	spectrum->Init();

	particle = new ParticleSystem( L"Particle", ObjectManager::Get()->GetCamera( ECamera::Main ), EObject::UI, 128 );
	particle->Init();

	backGround = new Plane( L"BackGround", ObjectManager::Get()->GetCamera( ECamera::UI ), EObject::UI );
	backGround->GetComponent<Transform>()->SetScale( 1440.0f, 1440.0f, 1.0f );
	backGround->GetComponent<Transform>()->SetPosition( 0.0f, 0.0f, 999.0f );
	backGround->GetComponent<Mesh>()->GetVSCB().color = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 0.125f );
	backGround->GetComponent<Material>()->SetTexture( TextureManager::Get()->GetTexture( L"back.jpg" ) );
	backGround->GetComponent<Material>()->SetPixel( "PixelShaderTexture" );
	backGround->Init();
	

	centerImage = new Plane( L"CenterImage", GetCamera(), GetType() );
	centerImage->GetComponent<Transform>()->SetScale( aroundScale, aroundScale, 1.0f );
	centerImage->GetComponent<Material>()->SetPixel( "PS_Sphere" );
	centerImage->GetComponent<Material>()->SetTexture( TextureManager::Get()->GetTexture( L"back.jpg" ) );
	centerImage->Init();

	GameObject::Init();
}

void SoundPlayer::Frame()
{
	Update();
	spectrum->UpdateLength( lengthAmount );
	// 카메라 흔들기 효과 ( UI Cam )
	if ( isCameraShake == true )
	{
		//const float& shakeAmount( spectrum->GetRawBass() * shakePower );
		//const float& shakeSin( ::sin( Timer::Get()->GameTimer() * 3.141595f * 720.0f ) );
		//const float& shakeCos( ::cos( Timer::Get()->GameTimer() * 3.141595f * 720.0f ) );
		//Camera* cam( ObjectManager::Get()->GetCamera( ECamera::UI ) );

		//cam->GetComponent<Transform>()->SetPosition( shakeSin * shakeAmount, shakeCos * shakeAmount, 0.0f );
	}
	spectrum->Frame();
	particle->Frame();
	centerImage->Frame();
	backGround->Frame();
	
	GameObject::Frame();
}

void SoundPlayer::Render( ID3D11DeviceContext* context )
{
	//backGround->Render( context );
	particle->Render( context );

	//rocker2.lock();
	//{
		spectrum->Render( context );
	//} rocker2.unlock();

	centerImage->Render( context );
	GameObject::Render( context );
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
	if ( isCenterBass == true )
	{
		centerImage->GetComponent<Transform>()->SetScale( aroundScale + bassAmount, aroundScale + bassAmount, 1.0f );
		spectrum->UpdatePosition( aroundScale, bassAmount );
	}
}