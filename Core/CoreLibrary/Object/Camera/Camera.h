#pragma once
#include "..\\..\\Object\GameObject.h"

enum class ECamera { Main = 0, UI, ModelView };

class Camera : public GameObject
{
public:
	Camera();
	virtual ~Camera() = default;

public:
	const D3DXMATRIX& GetViewMatrix() const override { return viewMatrix; }
	const D3DXMATRIX& GetProjMatrix() const override { return projMatrix; }

public:
	virtual void Create( LONG width, LONG height ) = 0;
	virtual void CreateViewMatrix() = 0;
	virtual void CreateProjMatrix( LONG width, LONG height ) = 0;

protected:
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;
};

