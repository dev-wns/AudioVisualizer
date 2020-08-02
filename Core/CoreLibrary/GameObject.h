#pragma once
//#include "Camera.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"

enum class EObject : char {	Empty = 0, Map, Character, Effect, UI, };

class GameObject
{
protected: GameObject();
public:
	GameObject( const std::wstring& _name, GameObject* _cam, EObject _type = EObject::Empty );
	virtual ~GameObject() = default;

public:
	virtual void Init();
	virtual void Frame();
	virtual void Render( ID3D11DeviceContext* context );
	virtual void Release();

protected:
	virtual void PrevRender( ID3D11DeviceContext* context );
	virtual void PostRender( ID3D11DeviceContext* context );

public:
	void AddObject( GameObject* _obj );
	void RemoveObject( GameObject* _obj );
	void RemoveObject( const std::wstring& _name );
	GameObject* FindObject( GameObject* _obj );
	GameObject* FindObject( const std::wstring& _name );

public:
	void SetBillboard( bool billboard );
	void SetParent( GameObject* _obj );
	void RemoveParent();
	void SetCamera( GameObject* _cam );

public:
	const std::vector<GameObject*>& GetChild() const { return childs;      }
	const std::wstring& GetName() const				 { return objectName;  }
	GameObject* GetCamera() const					 { return applyCamera; }
	EObject GetType() const						     { return objectType;  }

public:
	void Clear( ID3D11DeviceContext* context );
	virtual GameObject* Clone() { return new GameObject( *this ); }

public:
	/* 
		- »ç¿ë¹ý -
		GetComponent<Transform>()->Translate( 100.0f, 0.0f, 0.0f );
		GetComponent<Material>()->BindTexture( TextureManager::GetTexture( Texture::Player_1 ) );
		GetComponent<Mesh>()->UpdateConstantBuffer();
	*/
	template< class _Ty > _Ty*		 GetComponent() { }
	template<           > Transform* GetComponent() { return dynamic_cast< Transform* > ( FindComponent( EComponent::Transform ) ); }
	template<           > Material*  GetComponent() { return dynamic_cast< Material* >  ( FindComponent( EComponent::Material )  ); }
	template<           > Mesh*      GetComponent() { return dynamic_cast< Mesh* >      ( FindComponent( EComponent::Mesh )      ); }

private:
	Component* FindComponent( EComponent type );

public:
	virtual const D3DXMATRIX& GetViewMatrix() const { return Matrix::Identity; }
	virtual const D3DXMATRIX& GetProjMatrix() const { return Matrix::Identity; }

protected:
	friend class ObjectManager;
	bool isEnable;
	bool isBillboard;
	EObject objectType;
	std::wstring objectName;
	GameObject* parent;
	GameObject* applyCamera;
	std::vector<GameObject*> childs; // children
	std::map<EComponent, Component*> components;
public:
	D3DXVECTOR4 color;
};