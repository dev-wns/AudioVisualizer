#include "StdAfx.hpp"
#include "Spectrum.h"
#include "Plane.h"
#include "ObjectManager.h"
#include <cmath>
#include "BufferUtility.h"

// =======================================================================================================================
// ***** Bar
// =======================================================================================================================
Bar::Bar( const std::wstring& _name, GameObject* _cam, EObject _oType ) : GameObject( _name, _cam, _oType )
{
	std::vector<PNCT_VERTEX> vertices;
	vertices.resize( 4 );
	vertices[0] = PNCT_VERTEX( D3DXVECTOR3( -1.0f, 1.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 0.0f, 0.0f ) );
	vertices[1] = PNCT_VERTEX( D3DXVECTOR3( 1.0f, 1.0f, 0.0f ),  D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 1.0f, 0.0f ) );
	vertices[2] = PNCT_VERTEX( D3DXVECTOR3( 1.0f, 0.0f, 0.0f ),  D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 1.0f, 1.0f ) );
	vertices[3] = PNCT_VERTEX( D3DXVECTOR3( -1.0f, 0.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 0.0f, 1.0f ) );

	std::vector<DWORD> indices;
	indices.resize( 6 );
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;
	GetComponent<Mesh>()->Set( vertices, indices );
}


// =======================================================================================================================
// ***** Spectrum
// =======================================================================================================================

void Spectrum::Init()
{
	std::vector<PNCT_VERTEX> vertices;
	vertices.resize( 4 );
	vertices[0] = PNCT_VERTEX( D3DXVECTOR3( -barScale, 1.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 0.0f, 0.0f ) );
	vertices[1] = PNCT_VERTEX( D3DXVECTOR3(  barScale, 1.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 1.0f, 0.0f ) );
	vertices[2] = PNCT_VERTEX( D3DXVECTOR3(  barScale, 0.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 1.0f, 1.0f ) );
	vertices[3] = PNCT_VERTEX( D3DXVECTOR3( -barScale, 0.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 0.0f, 1.0f ) );

	std::vector<DWORD> indices;
	indices.resize( 6 );
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;
	GetComponent<Mesh>()->Set( vertices, indices );

	SetBillboard( true );

	if ( maxSpectrum == 0 )
		throw;

	// 스펙트럼 바를 센터 이미지(원형)에 맞게 생성, 이동, 회전 시킴
	const float& degree( ( 180.0f / maxSpectrum ) * ( 3.14159265358979323846f / 180.0f ) );


	int instanceCount = 0;
	instanceData.resize( maxSpectrum * 2 );
	for ( UINT count = 0; count < maxSpectrum; count++ )
	{
		// Red -> Green -> Blue 그라데이션 색상
		int r = 0, g = 0, b = 0;
		const float& a( ( 1.0f - ( ( 1.0f / maxSpectrum * ( maxSpectrum - count ) ) ) ) / 0.25f );
		const int& X( static_cast < int >( ::floor( a ) ) );
		const int& Y( static_cast < int >( ::floor( 255 * ( a - X ) ) ) );
		switch ( X )
		{
			case 0: r = 255;     g = Y;       b = 0;   break;
			case 1: r = 255 - Y; g = 255;     b = 0;   break;
			case 2: r = 0;       g = 255;     b = Y;   break;
			case 3: r = 0;       g = 255 - Y; b = 255; break;
			case 4: r = Y;       g = 0;       b = 255; break;
			case 5: r = 255;     g = 0;       b = 255; break;
		}
		const D3DXVECTOR4 c( r / 255.0f, g / 255.0f, b / 255.0f, 1.0f );

		// 좌측스펙트럼
		GameObject* leftBar = new Bar( L"Left", GetCamera(), GetType() );
		leftBar->GetComponent<Transform>()->SetRotateZ( degree + degree * count );
		leftBar->GetComponent<Transform>()->SetPosition(
			D3DXVECTOR3( -leftBar->GetComponent<Transform>()->GetUp().x * 100.0f,
						  leftBar->GetComponent<Transform>()->GetSide().x * 100.0f, 0.0f ) );
		leftBar->GetComponent<Mesh>()->GetVSCB().color = c;
		leftBar->GetComponent<Material>()->SetPixel( "PixelShaderColor" );
		AddObject( leftBar );

		// 우측 스펙트럼
		GameObject* rightBar = new Bar( L"Right", GetCamera(), GetType() );
		rightBar->GetComponent<Transform>()->SetRotateZ( -degree * count );
		rightBar->GetComponent<Transform>()->SetPosition(
			D3DXVECTOR3( -rightBar->GetComponent<Transform>()->GetUp().x * 100.0f,
						  rightBar->GetComponent<Transform>()->GetSide().x * 100.0f, 0.0f ) );
		rightBar->GetComponent<Mesh>()->GetVSCB().color = c;
		rightBar->GetComponent<Material>()->SetPixel( "PixelShaderColor" );
		AddObject( rightBar );

		// 인스턴스 데이터 생성 ( 좌측, 우측 )
		D3DXMatrixTranspose( &instanceData[instanceCount].worldMatrix, &Matrix::Identity );
		instanceData[instanceCount++].color = c;

		D3DXMatrixTranspose( &instanceData[instanceCount].worldMatrix, &Matrix::Identity );
		instanceData[instanceCount++].color = c;
	}
	instanceBuffer = Utility::Buffer::CreateBuffer( D3D11_BIND_VERTEX_BUFFER, DxManager::Get()->GetDevice(), &instanceData.at( 0 ), ( UINT )instanceData.size(), sizeof( InstanceData ), true );

	GameObject::Init();
	GetComponent<Material>()->SetInstanceLayout();
	GetComponent<Material>()->SetPixel( "PS" );
}

void Spectrum::Frame()
{
	int count = 0;
	for ( GameObject* oneSpectrumBar : GetChild() )
	{
		oneSpectrumBar->Frame();
		D3DXMatrixTranspose( &instanceData[count++].worldMatrix, &oneSpectrumBar->GetComponent<Transform>()->GetLocalMatrix() );
	}

	if ( instanceBuffer )
	{
		static D3D11_MAPPED_SUBRESOURCE MappedResource = { 0, };
		DxManager::Get()->GetContext()->Map( instanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource );
		InstanceData* pInstance = ( InstanceData* )MappedResource.pData;

		memcpy( pInstance, &instanceData.at( 0 ), sizeof( InstanceData ) * instanceData.size() );
		DxManager::Get()->GetContext()->Unmap( instanceBuffer, 0 );
	}

	GetComponent<Transform>()->Frame();
	// GameObject::Frame();
}

void Spectrum::Render( ID3D11DeviceContext* context )
{
	GetComponent<Mesh>()->UpdateConstantBuffer( GetComponent<Transform>()->GetLocalMatrix(), ObjectManager::Get()->GetCamera( ECamera::UI )->GetViewMatrix(), ObjectManager::Get()->GetCamera( ECamera::UI )->GetProjMatrix() );
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

	context->DrawIndexedInstanced( GetComponent<Mesh>()->numIndex, ( UINT )instanceData.size(), 0, 0, 0 );
	Clear( context );

	//GameObject::Render( context );
}

void Spectrum::UpdatePosition( const float& _aroundScale, const float& _bassAmount )
{
	// 베이스 음에 따른 스펙트럼바 위치 조절
	const std::vector<GameObject*>& childList( GetChild() );
	for ( UINT count = 0; count < maxSpectrum * 2; count++ )
	{
		childList[count]->GetComponent<Transform>()->SetPosition(
			D3DXVECTOR3( -( childList[count]->GetComponent<Transform>()->GetUp().x ) * ( _aroundScale + 5.0f + _bassAmount ),
				( childList[count]->GetComponent<Transform>()->GetSide().x ) * ( _aroundScale + 5.0f + _bassAmount ), 10.0f ) );
	}
}

void Spectrum::UpdateLength( const float& _lengthAmount )
{
	const float& spf( Timer::Get()->SPF() );
	std::map<ESoundCount, float*>& spectrum( SoundManager::Get()->GetSpectrum() );
	const std::vector<GameObject*>& childList( GetChild() );
	UINT spectrumCount = 0;

	for ( UINT count = 0; count < maxSpectrum * 2; spectrumCount++)
	{
		const float& value( ( ( spectrum[ESoundCount::S4096L][spectrumCount] + spectrum[ESoundCount::S4096R][spectrumCount] ) * 0.5f ) );
		// 음악에 따라 스펙트럼바 높낮이 조절
		const float& calc( value * _lengthAmount );
		const D3DXVECTOR3& scl( childList[count]->GetComponent<Transform>()->GetScale() );

		

		if ( scl.y < calc )
		{
			childList[count]->GetComponent<Transform>()->ScalingY( calc * 15.0f * spf );
			if ( scl.y > calc )
				childList[count]->GetComponent<Transform>()->SetScaleY( calc );
		}
		else
			childList[count]->GetComponent<Transform>()->ScalingY( -( 50.0f + ( ( ( scl.y * 3.5f ) / 18.0f ) * 40.71f ) ) * spf ); // 42

		if ( scl.y < 0.0f )
			childList[count]->GetComponent<Transform>()->SetScaleY( 0.0f );

//		if ( scl.y < calc )
//		{
//			childList[count]->GetComponent<Transform>()->SetScaleY( calc );
//		}
//
//		if ( scl.y > 0.0f )
//		{
//			//childList[count]->GetComponent<Transform>()->ScalingY( -( 50.0f + ( ( ( scl.y * 3.0f ) / 18.0f ) * 40.71f ) ) * spf ); // 42
//			//childList[count]->GetComponent<Transform>()->ScalingY( -( 100.0f + ( ( ( scl.y * 4.0f ) / 18.0f ) * 50.71f ) ) * spf ); // 42
//			if ( scl.y < 0.0f )
//			{
//				childList[count]->GetComponent<Transform>()->SetScaleY( calc );
//			}
//		}
//		else
//		{
//			childList[count]->GetComponent<Transform>()->SetScaleY( calc );
//		}

		childList[count + 1]->GetComponent<Transform>()->SetScale( childList[count]->GetComponent<Transform>()->GetScale() );
		count += 2;
	}
}