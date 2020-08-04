#pragma once
#include "..\\Standard\Singleton.hpp"
#include "..\\Object\Camera\Camera.h"

/* 
	������Ʈ���� �������ִ� Ŭ���� �Դϴ�.
	Empty, Character, Effect, UI, Camera... ���� ������Ʈ�� ��Ƶΰ� 
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
	Camera* GetCamera( ECamera _camType );
	void ResizeClient( UINT width, UINT height );

public:
	const std::map<ECamera, Camera*>& GetCameras() { return cameras; }

private:
	friend class Singleton<ObjectManager>;
	Camera* curCamera;
	std::map<ECamera, Camera*> cameras;
	std::map<EObject, std::list<GameObject*>> objects;
};