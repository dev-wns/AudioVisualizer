#pragma once
#include "GameObject.h"

class Line : public GameObject
{
public:
	Line( const std::wstring& _name, GameObject* _cam, EObject _type ) : GameObject( _name, _cam, _type ) { }
	virtual ~Line() = default;

public:
	void Init() override;
	void Update( const D3DXVECTOR3& start, const D3DXVECTOR3& end );
};

