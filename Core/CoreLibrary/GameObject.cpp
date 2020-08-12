#include "StdAfx.hpp"
#include "GameObject.h"
#include "Timer.h"
#include "BaseUtility.hpp"

GameObject::GameObject() : bVisibled( true ), bBillboard( false ), objectType( EObject::Empty ), objectName( ObjectName::Default )
{
	components.insert( std::make_pair( EComponent::Transform, new Transform() ) );
	components.insert( std::make_pair( EComponent::Mesh, new Mesh() ) );
	components.insert( std::make_pair( EComponent::Material, new Material() ) );
}

GameObject::GameObject( const std::wstring& _name, const GameObject* _cam, EObject _type ) : 
	bVisibled( true ), bBillboard( false ), objectType( _type ), objectName( _name ), applyCamera( _cam )
{
	components.insert( std::make_pair( EComponent::Transform, new Transform() ) );
	components.insert( std::make_pair( EComponent::Mesh, new Mesh() ) );
	components.insert( std::make_pair( EComponent::Material, new Material() ) );
}

GameObject* GameObject::FindObject( const std::wstring& _name )
{
	if ( _name.empty() == true ) 
		throw EmptyData( __FUNCTION__" - argument empty.\n" );

	const std::vector<GameObject*>::const_iterator& iter( std::find_if( std::cbegin( childs ), std::cend( childs ), 
		[&_name] ( GameObject* obj )->bool
		{
			return obj->GetName() == _name;
		} ) );

	return iter == std::cend( childs ) ? nullptr : *iter;
}

Component* GameObject::FindComponent( EComponent type )
{
	const auto& iter( components.find( type ) );
	if ( iter == components.end() ) throw EmptyData( __FUNCTION__" - the components iterator has reached the end.\n" );
	return dynamic_cast< Component* >( iter->second );
}

void GameObject::SetVisible( bool visible ) 
{
	bVisibled = visible; 
}

void GameObject::SetBillboard( bool _billboard )
{
	bBillboard = _billboard;
}

void GameObject::SetParent( GameObject* _parent )
{
	if ( _parent == nullptr )
		throw NullPointer( __FUNCTION__" - the argument is null reference.\n" );
	if ( parent != nullptr )
	{
		parent->RemoveObject( this );
	}

	parent = _parent;
}

void GameObject::SetCamera( GameObject* _cam )
{
	if ( _cam == nullptr ) 
		throw NullPointer( __FUNCTION__" - the argument is null reference.\n" );

	applyCamera = _cam;

	for ( GameObject* oneChild : childs )
	{
		oneChild->SetCamera( _cam );
	}
}
const std::vector<GameObject*>& GameObject::GetChilds() const
{ 
	return childs; 
}

const std::wstring& GameObject::GetName() const
{
	return objectName;  
}

const EObject GameObject::GetType() const
{
	return objectType;  
}

const GameObject* GameObject::GetParent() const
{
	return parent; 
}

const GameObject* GameObject::GetCamera() const 
{
	if ( applyCamera == nullptr ) 
		throw NullPointer( __FUNCTION__" - the apply camera is null reference.\n" );
	return applyCamera; 
}

void GameObject::AddObject( GameObject* _obj )
{
	if ( _obj == nullptr )
		throw NullPointer( __FUNCTION__" - the argument is null reference.\n" );
	_obj->SetParent( this );
	childs.emplace_back( _obj );
}

GameObject* GameObject::RemoveObject( GameObject* _obj )
{
	const std::vector<GameObject*>::iterator& it( std::find( std::begin( childs ), std::end( childs ), _obj ) );

	if ( it == std::end( childs ) ) return nullptr;
	childs.erase( it );

	return *it;
}

GameObject* GameObject::RemoveObject( const std::wstring& _name )
{
	const std::vector<GameObject*>::iterator& it ( std::find_if( std::begin( childs ), std::end( childs ), [&_name] (GameObject* obj)->bool
	{
		return obj->GetName() == _name;
	} ) );

	if ( it == std::end( childs ) ) return nullptr;
	childs.erase( it );

	return *it;
}

void GameObject::DeleteObject( GameObject* _obj )
{
	if ( _obj == nullptr )
		throw NullPointer( __FUNCTION__" - the argument is null reference.\n" );

	const GameObject* object( RemoveObject( _obj ) );
	if ( object == nullptr ) 
		throw NullPointer( __FUNCTION__" - the object is null reference.\n" );

	SafeDelete( object );
}

void GameObject::DeleteObject( const std::wstring& _name )
{
	if ( _name.empty() == true )
		throw NullPointer( __FUNCTION__" - the argument is null reference.\n" );

	GameObject* object( RemoveObject( _name ) );
	if ( object == nullptr )
		throw NullPointer( __FUNCTION__" - the object is null reference.\n" );

	SafeDelete( object );
}

void GameObject::Init()
{
	for ( std::pair<EComponent, Component*> oneComponent : components )
	{
		oneComponent.second->Init();
	}

	for ( GameObject* oneObject : childs )
	{
		oneObject->Init();
	}
}

void GameObject::FixedFrame()
{
	if ( Timer::Get()->IsFixedFrameRate() == false ) return;

	for ( GameObject* object : childs )
	{
		object->FixedFrame();
	}
}

void GameObject::Frame()
{
	if ( IsVisible() == false ) return;

	for ( std::pair<EComponent, Component*> oneComponent : components )
	{
		oneComponent.second->Frame();
	}

	// FixedFrame();

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
	if ( IsVisible() == false ) return;

	D3DXMATRIX parentMatrix( Matrix::Identity );
	if ( parent != nullptr )
		parentMatrix = parent->GetComponent<Transform>()->GetLocalMatrix();
	const D3DXMATRIX& world( parentMatrix * GetComponent<Transform>()->GetLocalMatrix() );

	D3DXMATRIX viewMatrix( applyCamera->GetViewMatrix() );
	GetComponent<Mesh>()->UpdateConstantBuffer( world, viewMatrix, applyCamera->GetProjMatrix() );

	if ( bBillboard == true )
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
	for ( std::map<EComponent, Component*>::iterator oneComponent = std::begin( components ); 
		  oneComponent != std::end( components ); oneComponent++ )
	{
		SafeRelease( oneComponent->second, true );
	}
	components.clear();

	for ( GameObject*& oneObject : childs )
	{
		SafeRelease( oneObject, true );
	}
	childs.clear();
}

void GameObject::Clear( ID3D11DeviceContext* context )
{
	if ( context == nullptr ) 
		throw NullPointer( __FUNCTION__" - the context is null reference.\n" );

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