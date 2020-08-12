#pragma once
#include "TextureManager.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"

enum class EObject : char {	Empty = 0, Map, Character, Effect, UI, };

class GameObject
{
public: 
	GameObject();
	GameObject( const std::wstring& _name, const GameObject* _cam, EObject _type = EObject::Empty );
	virtual ~GameObject() = default;

public:
	virtual void Init();
	virtual void Frame();
	virtual void Render( ID3D11DeviceContext* context );
	virtual void Release();

public:
	virtual void FixedFrame();

public:
	bool IsVisible()   { return bVisibled; }
	bool IsBillboard() { return bBillboard; }

public:
	void AddObject( GameObject* _obj );
	GameObject* FindObject( const std::wstring& _name );
	// childList에서만 제거
	GameObject* RemoveObject( GameObject* _obj );
	GameObject* RemoveObject( const std::wstring& _name );
	// 넘어온 인자까지 제거
	void DeleteObject( GameObject* _obj );
	void DeleteObject( const std::wstring& _name );

public:
	void SetParent( GameObject* _obj );
	void SetVisible( bool isVisible );
	void SetBillboard( bool isBillboard );
	void SetCamera( GameObject* _cam );

public:
	const std::vector<GameObject*>& GetChilds() const;
	const std::wstring& GetName()			    const;
	const EObject GetType()					    const;
	const GameObject* GetParent()			    const;
	const GameObject* GetCamera()			    const;

public:
	/* 
		- 사용법 -
		GetComponent<Transform>()->Translate( 100.0f * Timer::Get()->GetSPF(), 0.0f, 0.0f );
		GetComponent<Material>()->SetTexture( TextureManager::GetTexture( Resource::BackGround ) );
		GetComponent<Mesh>()->UpdateConstantBuffer();
	*/
	template< class _Ty > _Ty*		 GetComponent() { }
	template<           > Transform* GetComponent() { return dynamic_cast< Transform* > ( FindComponent( EComponent::Transform ) ); }
	template<           > Material*  GetComponent() { return dynamic_cast< Material* >  ( FindComponent( EComponent::Material )  ); }
	template<           > Mesh*      GetComponent() { return dynamic_cast< Mesh* >      ( FindComponent( EComponent::Mesh )      ); }

public:
	// Camera Object Override 용 메서드
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
	const GameObject* applyCamera;
	std::vector<GameObject*> childs;
	std::map<EComponent, Component*> components;
};