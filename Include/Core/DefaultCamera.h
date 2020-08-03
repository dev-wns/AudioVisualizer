#pragma once
#include "Camera.h"

class DefaultCamera : public Camera
{
public:
	DefaultCamera()			 = default;
	virtual ~DefaultCamera() = default;

public:
	void Create( LONG width, LONG height ) override;
	void CreateProjMatrix( LONG width, LONG height ) override;
	void CreateViewMatrix() override;
};

