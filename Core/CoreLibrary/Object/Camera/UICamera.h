#pragma once
#include "Camera.h"

class UICamera : public Camera
{
public:
	UICamera()			= default;
	virtual ~UICamera() = default;

public:
	void Create( LONG width, LONG height ) override;
	void CreateViewMatrix() override;
	void CreateProjMatrix( LONG width, LONG height ) override;

public:
	void Frame() override;
};

