#pragma once
#include "GameObject.h"

class Line : public GameObject
{
public:
	Line( const std::wstring& _name, const GameObject* _cam, EObject _type );
	virtual ~Line() = default;

public:
	void Init() override;
	void Update( const D3DXVECTOR3& start, const D3DXVECTOR3& end );
};

