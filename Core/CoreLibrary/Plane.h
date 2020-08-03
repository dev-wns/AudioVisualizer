#pragma once
#include "GameObject.h"

class Plane : public GameObject
{
public:
	Plane( const std::wstring& _name, GameObject* _cam, EObject _type ) : GameObject( _name, _cam, _type ) { }
	virtual ~Plane() = default;

public:
	void Init() override;
};