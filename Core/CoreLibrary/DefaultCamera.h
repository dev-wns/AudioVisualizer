#pragma once
#include "Camera.h"

class DefaultCamera : public Camera
{
public:
	DefaultCamera()			 = default;
	virtual ~DefaultCamera() = default;

public:
	void Create( LONG width, LONG height ) override
	{
		D3DXMatrixLookAtLH( &viewMatrix, &Vector3::Backward, &Vector3::Zero, &Vector3::Up );
		// Fovy, Aspect, Near, Far
		D3DXMatrixPerspectiveFovLH( &projMatrix,
			static_cast< FLOAT >( D3DX_PI * 0.25f ), 
			static_cast< FLOAT >( width / height ), 0.1f, 10000.0f );
	}
	void CreateProjMatrix( LONG width, LONG height ) override
	{
		D3DXMatrixPerspectiveFovLH( &projMatrix,
			static_cast< FLOAT >( D3DX_PI * 0.25f ),
			static_cast< FLOAT >( width / height ), 0.1f, 10000.0f );
	}

	void CreateViewMatrix() override
	{
		D3DXMatrixLookAtLH( &viewMatrix, &Vector3::Backward, &Vector3::Zero, &Vector3::Up );
	}

private:

};

