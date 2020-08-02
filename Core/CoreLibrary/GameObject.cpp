#include "StdAfx.hpp"
#include "GameObject.h"
#include "plane.h"

GameObject::GameObject()
{
	components.insert( std::make_pair( EComponent::Transform, new Transform() ) );
	components.insert( std::make_pair( EComponent::Mesh, new Mesh() ) );
	components.insert( std::make_pair( EComponent::Material, new Material() ) );
}
GameObject::GameObject( const std::wstring& _name, GameObject* _cam, EObject _type )
					 : objectName( _name ), applyCamera( _cam ), objectType( _type ), isBillboard( false )
{
	components.insert( std::make_pair( EComponent::Transform, new Transform() ) );
	components.insert( std::make_pair( EComponent::Mesh, new Mesh() ) );
	components.insert( std::make_pair( EComponent::Material, new Material() ) );
}

GameObject* GameObject::FindObject( GameObject* _obj )
{
	_obj;
	return nullptr;
}

GameObject* GameObject::FindObject( const std::wstring& _name )
{
	_name;
	return nullptr;
}

Component* GameObject::FindComponent( EComponent type )
{
	const auto& iter( components.find( type ) );
	if ( iter == components.end() ) throw;
	return dynamic_cast< Component* >( iter->second );
}

void GameObject::SetBillboard( bool billboard )
{
	isBillboard = billboard;
}

void GameObject::SetParent( GameObject* _obj )
{
	if ( _obj == nullptr ) throw;

	parent = _obj;
}

void GameObject::SetCamera( GameObject* _cam )
{
	if ( _cam == nullptr ) throw;

	applyCamera = _cam;

	for ( GameObject* oneChild : childs )
	{
		oneChild->SetCamera( _cam );
	}
}

void GameObject::AddObject( GameObject* _obj )
{
	if ( _obj == nullptr ) throw;

	_obj->SetParent( this );
	childs.emplace_back( _obj );
}

void GameObject::RemoveObject( GameObject* _obj )
{
	const std::vector<GameObject*>::iterator& it( std::find( std::begin( childs ), std::end( childs ), _obj ) );

	if ( it == std::end( childs ) ) return;

	delete *it;
	*it = nullptr;
	childs.erase( it );
}

void GameObject::RemoveObject( const std::wstring& _name )
{
	const std::vector<GameObject*>::iterator& it ( std::find_if( std::begin( childs ), std::end( childs ), [&_name] (GameObject* obj)->bool
	{
		return obj->GetName() == _name;
	} ) );

	if ( it == std::end( childs ) ) return;

	delete *it;
	*it = nullptr;
	childs.erase( it );
}

void GameObject::RemoveParent()
{
	if ( parent == nullptr ) return;

	parent = nullptr;
}

void GameObject::Init()
{
	//applyCamera = new Camera();
	//applyCamera->CreateViewMatrix();
	//applyCamera->CreateProjMatrix( 800, 600 );

	for ( std::pair<EComponent, Component*> oneComponent : components )
	{
		oneComponent.second->Init();
	}

	for ( GameObject* oneObject : childs )
	{
		oneObject->Init();
	}
}

void GameObject::Frame()
{
	// transform.Frame();

	for ( std::pair<EComponent, Component*> oneComponent : components )
	{
		oneComponent.second->Frame();
	}


	for ( GameObject* oneObject : childs )
	{
		oneObject->Frame();
	}
}

void GameObject::PrevRender( ID3D11DeviceContext* context )
{
	for ( std::pair<EComponent, Component*> oneComponent : components )
	{
		oneComponent.second->PrevRender();
	}

	for ( GameObject* oneObject : childs )
	{
		oneObject->PrevRender( context );
	}
}

void GameObject::Render( ID3D11DeviceContext* context )
{
	D3DXMATRIX parentMatrix( Matrix::Identity );
	if ( parent != nullptr )
		parentMatrix = parent->GetComponent<Transform>()->GetLocalMatrix();
	const D3DXMATRIX& world( parentMatrix * GetComponent<Transform>()->GetLocalMatrix() );

	D3DXMATRIX viewMatrix( applyCamera->GetViewMatrix() );
	GetComponent<Mesh>()->UpdateConstantBuffer( world, viewMatrix, applyCamera->GetProjMatrix() );

	if ( isBillboard == true )
	{
		viewMatrix._41 = 0.0f; viewMatrix._42 = 0.0f; viewMatrix._43 = 0.0f;
		D3DXMatrixInverse( &viewMatrix, nullptr, &viewMatrix );
	}

	for ( std::pair<EComponent, Component*> oneComponent : components )
	{
		oneComponent.second->Render();
	}

	Clear( context );

	for ( GameObject* oneObject : childs )
	{
		oneObject->Render( context );
	}

	// PrevRender( context );
	// PostRender( context );
}

void GameObject::PostRender( ID3D11DeviceContext* context )
{
	for ( std::pair<EComponent, Component*> oneComponent : components )
	{
		oneComponent.second->PostRender();
	}


	for ( GameObject* oneObject : childs )
	{
		oneObject->PostRender( context );
	}
}

void GameObject::Release()
{
	for ( std::pair<EComponent, Component*> oneComponent : components )
	{
		SafeRelease( oneComponent.second );
	}

	for ( GameObject* oneObject : childs )
	{
		SafeRelease( oneObject );
	}
}

void GameObject::Clear( ID3D11DeviceContext* context )
{
	if ( context == nullptr ) return;

	ID3D11ShaderResourceView* pSRVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	//ID3D11RenderTargetView* pRTVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	//ID3D11DepthStencilView* pDSV = nullptr;
	//ID3D11Buffer* pBuffers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	//ID3D11SamplerState* pSamplers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	//UINT StrideOffset[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	// Shaders
	context->VSSetShader( nullptr, nullptr, 0 );
	context->HSSetShader( nullptr, nullptr, 0 );
	context->DSSetShader( nullptr, nullptr, 0 );
	context->GSSetShader( nullptr, nullptr, 0 );
	context->PSSetShader( nullptr, nullptr, 0 );

	// IA clear
	//context->IASetVertexBuffers( 0, 16, pBuffers, StrideOffset, StrideOffset );
	//context->IASetIndexBuffer( nullptr, DXGI_FORMAT_R32_UINT, 0 );
	//context->IASetInputLayout( nullptr );

	// Constant buffers
	//context->VSSetConstantBuffers( 0, 14, pBuffers );
	//context->HSSetConstantBuffers( 0, 14, pBuffers );
	//context->DSSetConstantBuffers( 0, 14, pBuffers );
	//context->GSSetConstantBuffers( 0, 14, pBuffers );
	//context->PSSetConstantBuffers( 0, 14, pBuffers );

	// Resources
	context->VSSetShaderResources( 0, 16, pSRVs );
	context->HSSetShaderResources( 0, 16, pSRVs );
	context->DSSetShaderResources( 0, 16, pSRVs );
	context->GSSetShaderResources( 0, 16, pSRVs );
	context->PSSetShaderResources( 0, 16, pSRVs );

	// Samplers
	//context->VSSetSamplers( 0, 16, pSamplers );
	//context->HSSetSamplers( 0, 16, pSamplers );
	//context->DSSetSamplers( 0, 16, pSamplers );
	//context->GSSetSamplers( 0, 16, pSamplers );
	//context->PSSetSamplers( 0, 16, pSamplers );

	// Render targets
	//context->OMSetRenderTargets( 8, pRTVs, pDSV );

	// States
	//FLOAT blendFactor[4] = { 0,0,0,0 };
	//context->OMSetBlendState( nullptr, blendFactor, 0xFFFFFFFF );
	//context->OMSetDepthStencilState( nullptr, 0 );
	//context->RSSetState( nullptr );
}