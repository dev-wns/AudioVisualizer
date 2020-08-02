#include "StdAfx.hpp"
#include "MusicPlayer.h"
#include "ObjectManager.h"
#include "DxManager.h"

void MusicPlayer::Init()
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

	// 스펙트럼과 파티클의 프레임 렌더링 쓰레드로 따로 돌리기
	//rocker1.lock();
	//{
	//	DxManager::Get()->SetState( EBlend::Alpha );
	//	DxManager::Get()->SetState( EDepthStencil::Disable );
	//	std::thread t1( [&] ()
	//	{
	//		while ( true )
	//			particle->Frame();
	//	} );
	//	t1.detach();
	//} rocker1.unlock();

	//rocker2.lock();
	//{
	//	DxManager::Get()->SetState( EBlend::Alpha );
	//	DxManager::Get()->SetState( EDepthStencil::Disable );
	//	std::thread t2( [&] ()
	//	{
	//		while ( true )
	//		{
	//			spectrum->Frame();
	//		}
	//	} );
	//	t2.detach();
	//}rocker2.unlock();

	//std::thread t3( [&] ()
	//{
	//	while ( true )
	//	{
	//		Update();
	//	}
	//} );
	//t3.detach();

	GameObject::Init();
}

void MusicPlayer::Frame()
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

void MusicPlayer::Render( ID3D11DeviceContext* context )
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