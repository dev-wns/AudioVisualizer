#pragma once
#include "Camera.h"


class UICamera : public Camera
{
public:
	UICamera()			= default;
	virtual ~UICamera() = default;

public:
	void Create( LONG width, LONG height ) override
	{
		D3DXMatrixLookAtLH( &viewMatrix, &Vector3::Backward, &Vector3::Zero, &Vector3::Up );
		D3DXMatrixOrthoOffCenterLH( &projMatrix, -width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, 0.0f, 1000.0f );
	}

	void CreateViewMatrix() override
	{
		D3DXMatrixLookAtLH( &viewMatrix, &Vector3::Backward, &Vector3::Zero, &Vector3::Up );
	}

	void CreateProjMatrix( LONG width, LONG height ) override
	{
		D3DXMatrixOrthoOffCenterLH( &projMatrix, -width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, 0.0f, 1000.0f );
	}

public:
	void Frame() override
	{
		viewMatrix._41 = GetComponent<Transform>()->GetPosition().x;
		viewMatrix._42 = GetComponent<Transform>()->GetPosition().y;

		GameObject::Frame();
	}
};

