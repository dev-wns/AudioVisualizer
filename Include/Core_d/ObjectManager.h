#pragma once
#include "Singleton.hpp"
#include "Camera.h"
#include "DxManager.h"

/* 
	������Ʈ���� �������ִ� Ŭ���� �Դϴ�.
	Empty, Character, Effect, UI, Camera �� ������Ʈ�� ��Ƶΰ� 
	������Ʈ Ÿ�Կ� ���� ������ ������ �����˴ϴ�.
*/ 
class ObjectManager : public Singleton<ObjectManager>
{
private:		 ObjectManager() = default;
public:	virtual ~ObjectManager() = default;

public:
	void PrevInit();
	void PostInit();
	void Frame();
	void Render( ID3D11DeviceContext* context );
	void Release();

public:
	void AddObject( GameObject* _obj );
	void RemoveObject( GameObject* _obj );
	void RemoveObject( const std::wstring& _name );

public:
	void SetCamera( ECamera _cam );
	Camera* GetCamera( ECamera _camType )
	{
		const std::map<ECamera, Camera*>::const_iterator& iter( cameras.find( _camType ) );
		if ( iter == std::cend( cameras ) )
		{
			// ������ ��ȯ�ұ�?? ��ΰ�� throw?
			return curCamera;
		}

		return iter->second;
	}
	void ResizeClient( UINT width, UINT height )
	{
		for ( const std::pair<ECamera, Camera*>& cam : cameras )
		{
			cam.second->CreateProjMatrix( width, height );
		}
	}

	std::map<ECamera, Camera*>& GetCameras() { return cameras; }

private:
	friend class Singleton<ObjectManager>;
	Camera* curCamera;
	std::map<ECamera, Camera*> cameras;
	std::map<EObject, std::list<GameObject*>> objects;
};