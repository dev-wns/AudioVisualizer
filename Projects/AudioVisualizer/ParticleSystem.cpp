#include "StdAfx.hpp"
#include "ParticleSystem.h"
#include "BaseUtility.hpp"
#include "MyRandom.h"
#include "Timer.h"
#include "SoundManager.h"
#include "DxManager.h"
#include "ObjectManager.h"

Particle::Particle( const std::wstring _name, GameObject* _cam, EObject _type, bool* _isRainbow ) : 
	GameObject( _name, _cam, _type ), bRainbow( *_isRainbow ), startPos( Vector3::Zero ), direction( Vector3::Backward ),
	defaultColor( D3DXVECTOR4( 1.0f, 1.0f, 1.0f, MyRandom::Get()->GetRandomFloat( 0.1f, 1.0f ) ) ),
	rainbowColor( D3DXVECTOR4( MyRandom::Get()->GetRandomFloat( 0.0f, 1.0f ), MyRandom::Get()->GetRandomFloat( 0.0f, 1.0f ),
	  					       MyRandom::Get()->GetRandomFloat( 0.0f, 1.0f ), MyRandom::Get()->GetRandomFloat( 0.5f, 1.0f ) ) ),
	moveSpeed( MyRandom::Get()->GetRandomFloat( 1.0f, 200.0f ) ), 
	respawnDelay( 0.0f ), timer( 0.0f )

{
	const float& width( static_cast< float >( DxManager::Get()->GetClientRect().right ) );
	GetComponent<Transform>()->SetPosition( MyRandom::Get()->GetRandomFloat( -width, width ),
											MyRandom::Get()->GetRandomFloat( -width, width ),
											MyRandom::Get()->GetRandomFloat( 0.0f, 10000.0f ) );

	const float& scl( MyRandom::Get()->GetRandomFloat( 10.0f, 25.0f ) );
	GetComponent<Transform>()->SetScale( scl / 2.0f, scl, 1.0f );
	GetComponent<Material>()->SetColor( D3DXVECTOR4( 1.0f, 1.0f, 1.0f, MyRandom::Get()->GetRandomFloat( 0.43f, 1.0f ) ) );
}

Particle::~Particle() { }

void Particle::Init()
{
	std::vector<PNCT_VERTEX> vertices;
	vertices.resize( 4 );
	vertices[0] = PNCT_VERTEX( D3DXVECTOR3( -1.0f, 1.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 0.0f, 0.0f ) );
	vertices[1] = PNCT_VERTEX( D3DXVECTOR3( 1.0f, 1.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 1.0f, 0.0f ) );
	vertices[2] = PNCT_VERTEX( D3DXVECTOR3( 1.0f, -1.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 1.0f, 1.0f ) );
	vertices[3] = PNCT_VERTEX( D3DXVECTOR3( -1.0f, -1.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 0.0f, 1.0f ) );

	std::vector<DWORD> indices;
	indices.resize( 6 );
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;
	GetComponent<Mesh>()->Set( vertices, indices );

	GameObject::Init();
}

void Particle::Frame()
{
	const float& spf( Timer::Get()->GetSPF() );
	const float* spec( SoundManager::Get()->GetSpectrum()[ESoundCount::S512] );

	// 색상 체크
	if ( bRainbow == true )
		GetComponent<Mesh>()->GetVSCB().color = rainbowColor;
	else
		GetComponent<Mesh>()->GetVSCB().color = defaultColor;

	const float& accSpeed( ( spec[0] + spec[1] + spec[2] + spec[3] + spec[4] ) * 450.0f );
	const float& speed( moveSpeed + ( moveSpeed * accSpeed ) );
	const D3DXVECTOR3& value( direction * speed * spf );
	GetComponent<Transform>()->Translate( value );

	GameObject::Frame();
}

/////////////////////////////////////////////////////////////////////////////////////////////////

ParticleSystem::ParticleSystem( const std::wstring _name, GameObject* _cam, EObject _type, UINT _maxParticle ) : 
	GameObject( _name, _cam, _type ), bRainbow( false ), maxParticle( _maxParticle ) { }

void ParticleSystem::Init()
{
	std::vector<PNCT_VERTEX> vertices;
	vertices.resize( 4 );
	vertices[0] = PNCT_VERTEX( D3DXVECTOR3( -1.0f, 1.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 0.0f, 0.0f ) );
	vertices[1] = PNCT_VERTEX( D3DXVECTOR3( 1.0f, 1.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 1.0f, 0.0f ) );
	vertices[2] = PNCT_VERTEX( D3DXVECTOR3( 1.0f, -1.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 1.0f, 1.0f ) );
	vertices[3] = PNCT_VERTEX( D3DXVECTOR3( -1.0f, -1.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 0.0f, 1.0f ) );

	std::vector<DWORD> indices;
	indices.resize( 6 );
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;
	GetComponent<Mesh>()->Set( vertices, indices );

	instanceData.resize( maxParticle );
	for ( UINT count = 0; count < maxParticle; count++ )
	{
		Particle* newParticle = new Particle( L"Particle", GetCamera(), GetType(), &bRainbow );
		AddObject( newParticle );
		D3DXMatrixTranspose( &instanceData[count].worldMatrix, &Matrix::Identity );
		instanceData[count].color = newParticle->GetComponent<Material>()->GetColor();
	}
	instanceBuffer = Utility::Buffer::CreateBuffer( D3D11_BIND_VERTEX_BUFFER, DxManager::Get()->GetDevice(), &instanceData.at( 0 ), ( UINT )instanceData.size(), sizeof( InstanceData ), true );

	GameObject::Init();

	GetComponent<Material>()->SetInstanceLayout();
}

void ParticleSystem::Frame()
{
	int count( 0 );
	const float& width( static_cast< float >( DxManager::Get()->GetClientRect().right ) );
	for ( GameObject* oneParticle : GetChild() )
	{
		const D3DXVECTOR3& pos( oneParticle->GetComponent<Transform>()->GetPosition() );
		if ( pos.z < 0.0f || ( ( pos.x > -150.0f && pos.y < 150.0f ) && ( pos.x < 150.0f && pos.y > -150.0f ) ) )
		{
			oneParticle->GetComponent<Transform>()->SetPosition(
				MyRandom::Get()->GetRandomFloat( -width, width ),
				MyRandom::Get()->GetRandomFloat( -width, width ),
				10000.0f );
		}
		oneParticle->Frame();
		D3DXMatrixTranspose( &instanceData[count].worldMatrix, &oneParticle->GetComponent<Transform>()->GetLocalMatrix() );
		instanceData[count++].color = oneParticle->GetComponent<Material>()->GetColor();
	}

	if ( instanceBuffer )
	{
		static D3D11_MAPPED_SUBRESOURCE MappedResource = { 0, };
		DxManager::Get()->GetContext()->Map( instanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource );
		InstanceData* instance( ( InstanceData* )MappedResource.pData );

		::memcpy( instance, &instanceData.at( 0 ), sizeof( InstanceData ) * instanceData.size() );
		DxManager::Get()->GetContext()->Unmap( instanceBuffer, 0 );
	}
}

void ParticleSystem::Render( ID3D11DeviceContext* context )
{
	GetComponent<Mesh>()->UpdateConstantBuffer( GetComponent<Transform>()->GetLocalMatrix(), GetCamera()->GetViewMatrix(), GetCamera()->GetProjMatrix() );
	GetComponent<Mesh>()->UpdateVertex();

	context->IASetPrimitiveTopology( ( D3D11_PRIMITIVE_TOPOLOGY )D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	ID3D11InputLayout* layout( GetComponent<Material>()->GetLayout() );
	context->IASetInputLayout( layout );

	DxManager::Get()->SetState( EBlend::Alpha );
	DxManager::Get()->SetState( EDepthStencil::Disable );
	DxManager::Get()->SetState( ESampler::Default );

	ID3D11Buffer* vb[2] = { GetComponent<Mesh>()->GetVertexBuffer(), instanceBuffer };
	UINT strides[2] = { sizeof( PNCT_VERTEX ), sizeof( InstanceData ) };
	UINT offsets[2] = { 0, 0 };
	context->IASetVertexBuffers( 0, 2, vb, strides, offsets );
	context->IASetIndexBuffer( GetComponent<Mesh>()->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0 );
	context->VSSetConstantBuffers( 0, 1, &GetComponent<Mesh>()->GetConstantBuffer() );
	context->PSSetConstantBuffers( 0, 1, &GetComponent<Mesh>()->GetConstantBuffer() );
	context->VSSetShader( GetComponent<Material>()->GetVertexShader(), NULL, 0 );
	context->PSSetShader( GetComponent<Material>()->GetPixelShader(), NULL, 0 );

	context->DrawIndexedInstanced( GetComponent<Mesh>()->GetIndexCount(), static_cast< UINT >( instanceData.size() ), 0, 0, 0 );
	GameObject::Clear( context );
}

void ParticleSystem::Release()
{
	instanceData.clear();
	SafeRelease( instanceBuffer );
	GameObject::Release();
}
