#pragma once
#include "..\\Managed\TextureManager.h"
#include "..\\Components\Component\Transform.h"
#include "..\\Components\Component\Mesh.h"
#include "..\\Components\Component\Material.h"

enum class EObject : char {	Empty = 0, Map, Character, Effect, UI, };

class GameObject
{
public: 
	GameObject();
	GameObject( const std::wstring& _name, GameObject* _cam, EObject _type = EObject::Empty );
	virtual ~GameObject() = default;

public:
	virtual void Init();
	virtual void Frame();
	virtual void Render( ID3D11DeviceContext* context );
	virtual void Release();

public:
	virtual void FixedFrame();

public:
	void SetVisible( bool visible ) { bVisibled = visible; }
	bool IsVisible() { return bVisibled; }

public:
	void AddObject( GameObject* _obj );
	// childList에서만 제거
	GameObject* RemoveObject( GameObject* _obj );
	GameObject* RemoveObject( const std::wstring& _name );
	// 넘어온 인자까지 제거
	void DeleteObject( GameObject* _obj );
	void DeleteObject( const std::wstring& _name );
	GameObject* FindObject( GameObject* _obj );
	GameObject* FindObject( const std::wstring& _name );

public:
	void SetBillboard( bool bBillboard );
	void SetParent( GameObject* _obj );
	void RemoveParent();
	void SetCamera( GameObject* _cam );

public:
	const std::vector<GameObject*>& GetChild() const { return childs;      }
	const std::wstring& GetName() const				 { return objectName;  }
	GameObject* GetCamera() const					 { return applyCamera; }
	const EObject GetType() const						     { return objectType;  }

public:
	/* 
		- 사용법 -
		GetComponent<Transform>()->Translate( 100.0f, 0.0f, 0.0f );
		GetComponent<Material>()->BindTexture( TextureManager::GetTexture( Texture::Player_1 ) );
		GetComponent<Mesh>()->UpdateConstantBuffer();
	*/
	template< class _Ty > _Ty*		 GetComponent() { }
	template<           > Transform* GetComponent() { return dynamic_cast< Transform* > ( FindComponent( EComponent::Transform ) ); }
	template<           > Material*  GetComponent() { return dynamic_cast< Material* >  ( FindComponent( EComponent::Material )  ); }
	template<           > Mesh*      GetComponent() { return dynamic_cast< Mesh* >      ( FindComponent( EComponent::Mesh )      ); }

public:
	virtual const D3DXMATRIX& GetViewMatrix() const { return Matrix::Identity; }
	virtual const D3DXMATRIX& GetProjMatrix() const { return Matrix::Identity; }

protected:
	void Clear( ID3D11DeviceContext* context );
	virtual GameObject* Clone() { return new GameObject( *this ); }

protected:
	virtual void PrevRender( ID3D11DeviceContext* context );
	virtual void PostRender( ID3D11DeviceContext* context );

private:
	Component* FindComponent( EComponent type );

private:
	friend class ObjectManager;
	bool bVisibled;
	bool bBillboard;
	EObject objectType;
	std::wstring objectName;
	GameObject* parent;
	GameObject* applyCamera;
	std::vector<GameObject*> childs;
	std::map<EComponent, Component*> components;
};