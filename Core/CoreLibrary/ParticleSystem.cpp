#include "StdAfx.hpp"
#include "ParticleSystem.h"
#include "BufferUtility.h"

Particle::Particle( const std::wstring _name, GameObject* _cam, EObject _type, bool* _isRainbow ) : GameObject( _name, _cam, _type ), isRainbow( *_isRainbow )
{
	const float& width( static_cast< float >( DxManager::Get()->GetClientRect().right ) );
	GetComponent<Transform>()->SetPosition(
		MyRandom::Get()->GetRandomFloat( -width, width ),
		MyRandom::Get()->GetRandomFloat( -width, width ),
		MyRandom::Get()->GetRandomFloat( 0.0f, 10000.0f ) );

	const float& scl( MyRandom::Get()->GetRandomFloat( 10.0f, 25.0f ) );
	GetComponent<Transform>()->SetScale( scl / 2.0f, scl, 1.0f );
	respawnDelay = 0.0f;// MyRandom::Get()->GetRandomFloat( 3.0f, 10.0f );
	moveSpeed = MyRandom::Get()->GetRandomFloat(1.0f, 100.0f );

	defaultColor = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, MyRandom::Get()->GetRandomFloat( 0.1f, 1.0f ) );
	color = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, MyRandom::Get()->GetRandomFloat( 0.43f, 1.0f ) );
	rainbowColor = D3DXVECTOR4(
		MyRandom::Get()->GetRandomFloat( 0.0f, 1.0f ),
		MyRandom::Get()->GetRandomFloat( 0.0f, 1.0f ),
		MyRandom::Get()->GetRandomFloat( 0.0f, 1.0f ),
		MyRandom::Get()->GetRandomFloat( 0.5f, 1.0f ) );

	isEnable = false;
	SetBillboard( false );
}

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
	const float& spf( Timer::Get()->SPF() );
	const float* spec( SoundManager::Get()->GetSpectrum()[ESoundCount::S512] );

	// 색상 체크
	if ( isRainbow == true )
		GetComponent<Mesh>()->GetVSCB().color = rainbowColor;
	else
		GetComponent<Mesh>()->GetVSCB().color = defaultColor;

	const float& accSpeed( ( spec[0] + spec[1] + spec[2] + spec[3] + spec[4] ) * 450.0f );
	const float& speed( moveSpeed + ( moveSpeed * accSpeed ) );
	const D3DXVECTOR3& value( direction * speed * spf );
	GetComponent<Transform>()->Translate( value );

	//// 이동 루틴
	//if ( isEnable == true )
	//{
	//	timer += spf;
	//	if ( respawnDelay < timer )
	//	{
	//		timer = 0.0f;
	//		isEnable = false;
	//	}
	//}
	//else
	//{
	//	const float& accSpeed( ( spec[0] + spec[1] + spec[2] + spec[3] + spec[4] ) * 150.0f );
	//	const float& speed( moveSpeed + ( moveSpeed * accSpeed ) );
	//	const D3DXVECTOR3& value( direction * speed * spf );
	//	GetComponent<Transform>()->Translate( value );
	//}
	GameObject::Frame();
}

/////////////////////////////////////////////////////////////////////////////////////////////////

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
		Particle* newParticle = new Particle( L"Particle", GetCamera(), GetType(), &isRainbow );
		//newParticle->GetComponent<Material>()->SetTexture( GetComponent<Material>()->GetTexture() );
		//newParticle->GetComponent<Material>()->SetPixel( "PS_Sphere" );
		AddObject( newParticle );
		D3DXMatrixTranspose( &instanceData[count].worldMatrix, &Matrix::Identity );
		instanceData[count].color = newParticle->color;
	}
	instanceBuffer = Utility::Buffer::CreateBuffer( D3D11_BIND_VERTEX_BUFFER, DxManager::Get()->GetDevice(), &instanceData.at(0), (UINT)instanceData.size(), sizeof( InstanceData ), true );

	GameObject::Init();

	GetComponent<Material>()->SetInstanceLayout();
}

void ParticleSystem::Frame() 
{
	const float& width( static_cast< float >( DxManager::Get()->GetClientRect().right ) );
	int count = 0;
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
		instanceData[count++].color = oneParticle->color;
	}

	if ( instanceBuffer )
	{
		static D3D11_MAPPED_SUBRESOURCE MappedResource = { 0, };
		DxManager::Get()->GetContext()->Map( instanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource );
		InstanceData* pInstance = ( InstanceData* )MappedResource.pData;		

		memcpy( pInstance, &instanceData.at( 0 ), sizeof( InstanceData ) * instanceData.size() );
		DxManager::Get()->GetContext()->Unmap( instanceBuffer, 0 );
	}
}

void ParticleSystem::Render( ID3D11DeviceContext* context )
{
	GetComponent<Mesh>()->UpdateConstantBuffer( GetComponent<Transform>()->GetLocalMatrix(), ObjectManager::Get()->GetCamera( ECamera::Main )->GetViewMatrix(), ObjectManager::Get()->GetCamera( ECamera::Main )->GetProjMatrix() );
	GetComponent<Mesh>()->UpdateVertex();

	context->IASetPrimitiveTopology( ( D3D11_PRIMITIVE_TOPOLOGY )D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	ID3D11InputLayout* layout( GetComponent<Material>()->layout );
	context->IASetInputLayout( layout );

	DxManager::Get()->SetState( EBlend::Alpha );
	DxManager::Get()->SetState( EDepthStencil::Disable );
	DxManager::Get()->SetState( ESampler::Default );

	ID3D11Buffer* vb[2] = { GetComponent<Mesh>()->vertexBuffer,	instanceBuffer };
	UINT strides[2] = { sizeof( PNCT_VERTEX ), sizeof( InstanceData ) };
	UINT offsets[2] = { 0, 0 };
	context->IASetVertexBuffers( 0, 2, vb, strides, offsets );
	context->IASetIndexBuffer( GetComponent<Mesh>()->indexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	context->VSSetConstantBuffers( 0, 1, &GetComponent<Mesh>()->vertexShaderConstantBuffer );
	context->PSSetConstantBuffers( 0, 1, &GetComponent<Mesh>()->vertexShaderConstantBuffer );
	context->VSSetShader( GetComponent<Material>()->vertexShader, NULL, 0 );
	context->PSSetShader( GetComponent<Material>()->pixelShader, NULL, 0 );
	
	context->DrawIndexedInstanced( GetComponent<Mesh>()->numIndex, (UINT)instanceData.size(), 0, 0, 0 );
	Clear( context );
}
