#pragma once
#include "StdAfx.hpp"

enum class EComponent {	Transform = 0, Material, Mesh, };

class Component
{
public:
	Component() = default;
	virtual ~Component() = default;

public:
	virtual void Init() { }
	virtual void Frame() { }
	virtual void PrevRender() { }
	virtual void Render() 
	{
		PrevRender();
		PostRender();
	}
	virtual void PostRender() { }
	virtual void Release() { }  
};

