#pragma once
#include "Camera.h"

class ModelViewCamera : public Camera
{
public:
	ModelViewCamera()		   = default;
	virtual ~ModelViewCamera() = default;

public:
	void Create( LONG width, LONG height ) override;
	void CreateViewMatrix() override;
	void CreateProjMatrix( LONG width, LONG height ) override;
};

