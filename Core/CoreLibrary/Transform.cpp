#include "StdAfx.hpp"
#include "Transform.h"
#include "BaseConst.hpp" 

Transform::Transform() : 
	worldMatrix( Matrix::Identity ), localMatrix( Matrix::Identity ),
	sclMatrix( Matrix::Identity ), rotMatrix( Matrix::Identity ), posMatrix( Matrix::Identity ),
	look( Vector3::Forward ), up( Vector3::Up ), side( Vector3::Right ),
	scl( Vector3::One ), rot( Quaternion::Zero ), pos( Vector3::Zero ) { }

void Transform::Frame()
{
	::D3DXMatrixScaling( &sclMatrix, scl.x, scl.y, scl.z );
	::D3DXMatrixRotationYawPitchRoll( &rotMatrix, rot.y, rot.x, rot.z );
	::D3DXMatrixTranslation( &posMatrix, pos.x, pos.y, pos.z );

	worldMatrix = localMatrix = sclMatrix * rotMatrix * posMatrix;

	side = { worldMatrix._11, worldMatrix._21, worldMatrix._31 };
	up    = { worldMatrix._12, worldMatrix._22, worldMatrix._32 };
	look  = { worldMatrix._13, worldMatrix._23, worldMatrix._33 };

	pos.x = worldMatrix._41;
	pos.y = worldMatrix._42;
	pos.z = worldMatrix._43;
}

void Transform::Frame( const D3DXMATRIX& parent )
{
	Frame();

	const D3DXMATRIX parentMatrix( Matrix::Identity );
	if ( parent == Matrix::Identity )
	{
		worldMatrix = parent * localMatrix;
	}
}