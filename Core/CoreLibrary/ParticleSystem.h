#pragma once
#include "BaseMath.hpp"
#include "GameObject.h"
#include "MyRandom.h"
#include "Timer.h"
#include "SoundManager.h"
#include "DxManager.h"
#include "ObjectManager.h"
#include "Line.h"

//#pragma pack(push, 1)
//struct InstanceData
//{
//	D3DXMATRIX worldMatrix;
//	D3DXVECTOR4 color;
//};
//#pragma pack(pop)

class Particle : public GameObject
{
public:
	Particle( const std::wstring _name, GameObject* _cam, EObject _type, bool* _isRainbow );
	virtual ~Particle() = default;

public:
	void Init() override;
	void Frame() override;

	D3DXVECTOR4 defaultColor;
private:
	friend class ParticleSystem;

	bool& isRainbow;
	D3DXVECTOR4 rainbowColor;

	D3DXVECTOR3 startPos;
	D3DXVECTOR3	direction = Vector3::Backward;

	float moveSpeed;
	float respawnDelay;
	float timer;
};



class ParticleSystem : public GameObject
{
public:
	ParticleSystem( const std::wstring _name, GameObject* _cam, EObject _type, UINT _maxParticle ) : GameObject( _name, _cam, _type ), maxParticle( _maxParticle ) { }
	virtual ~ParticleSystem() = default;

public:
	void Init() override;
	void Frame() override;
	void Render( ID3D11DeviceContext* context ) override;

private:
	std::vector<InstanceData> instanceData;
	ID3D11Buffer* instanceBuffer;
	bool isRainbow = false;
	UINT maxParticle;
};

//class Instancer : public GameObject
//{
//public:
//	void Initialized( GameObject* _object, UINT _count )
//	{
//		if ( _object == nullptr ) throw;
//		
//		InstanceObject = _object;
//		count = _count;
//		
//		datas.resize( count );
//		for ( int instanceCount = 0; instanceCount < count; instanceCount++ )
//		{
//			D3DXMatrixTranspose( &datas[instanceCount].worldMatrix, &Matrix::Identity );
//			datas[instanceCount].color = Color::White;
//		}
//
//		ID3D11Buffer* buffer( InstanceObject->GetComponent<Mesh>()->GetVertexBuffer() );
//		if ( buffer == nullptr ) throw;
//		buffers[0] = buffer;
//		buffers[1] = Utility::Buffer::CreateBuffer( D3D11_BIND_VERTEX_BUFFER, DxManager::Get()->GetDevice(), &datas.at( 0 ), ( UINT )datas.size(), sizeof( InstanceData ), true );
//
//		strides[0] = sizeof( PCT_VERTEX );
//		strides[1] = sizeof( InstanceData );
//
//		offsets[0] = 0;
//		offsets[1] = 0;
//
//		// 인스턴스 레이아웃 생성
//		InstanceObject->GetComponent<Material>()->SetInstanceLayout();
//	}
//
//	void UpdateInstanceBuffer()
//	{
//		static D3D11_MAPPED_SUBRESOURCE MappedResource = { 0, };
//		DxManager::Get()->GetContext()->Map( buffers[1], 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource );
//		InstanceData* pInstance = ( InstanceData* )MappedResource.pData;		// 바꿀 객체
//
//		memcpy( pInstance, &datas.at( 0 ), sizeof( InstanceData ) * datas.size() );
//		DxManager::Get()->GetContext()->Unmap( buffers[1], 0 );
//	}
//
//	std::vector<InstanceData>& GetData() { return datas; }
//
//	void Render( ID3D11DeviceContext* context ) override
//	{
//		GetComponent<Mesh>()->UpdateConstantBuffer( 
//			InstanceObject->GetComponent<Transform>()->GetLocalMatrix(),
//			InstanceObject->GetCamera()->GetViewMatrix(), 
//			InstanceObject->GetCamera()->GetProjMatrix() );
//
//		GetComponent<Mesh>()->UpdateVertexPCT();
//		context->IASetPrimitiveTopology( ( D3D11_PRIMITIVE_TOPOLOGY )D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
//
//		context->IASetInputLayout( InstanceObject->GetComponent<Material>()->layout );
//
//
//		DxManager::Get()->SetState( EBlend::Alpha );
//		DxManager::Get()->SetState( EDepthStencil::Disable );
//		DxManager::Get()->SetState( ESampler::Default );
//
//		context->IASetVertexBuffers( 0, 2, buffers, strides, offsets );
//		context->IASetIndexBuffer( InstanceObject->GetComponent<Mesh>()->indexBuffer, DXGI_FORMAT_R32_UINT, 0 );
//		context->VSSetConstantBuffers( 0, 1, &InstanceObject->GetComponent<Mesh>()->vertexShaderConstantBuffer );
//		context->PSSetConstantBuffers( 0, 1, &InstanceObject->GetComponent<Mesh>()->vertexShaderConstantBuffer );
//		context->VSSetShader( InstanceObject->GetComponent<Material>()->vertexShader, NULL, 0 );
//		context->PSSetShader( InstanceObject->GetComponent<Material>()->pixelShader, NULL, 0 );
//
//		UINT index( GetComponent<Mesh>()->numIndex );
//		context->DrawIndexedInstanced( index, ( UINT )datas.size(), 0, 0, 0 );
//		Clear( context );
//	}
//
//private:
//	GameObject* InstanceObject;      // 인스턴싱할 객체
//	std::vector<InstanceData> datas; // 인스턴스 데이터
//	UINT count;						 // 인스턴싱 할 개수
//	ID3D11Buffer* buffers[2];
//	UINT strides[2];
//	UINT offsets[2];
//};
