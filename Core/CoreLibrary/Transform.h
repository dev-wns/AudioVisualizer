#pragma once
#include "BaseMath.hpp"
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	virtual ~Transform() = default;

public:
	const D3DXMATRIX& GetWorldMatrix()  const { return worldMatrix; }
	const D3DXMATRIX& GetLocalMatrix()  const { return localMatrix; }
	const D3DXVECTOR3& GetPosition()    const { return pos; }
	const D3DXQUATERNION& GetRotation() const { return rot; }
	const D3DXVECTOR3& GetScale()       const { return scl; }
	const D3DXVECTOR3& GetForward()     const { return look; }
	const D3DXVECTOR3& GetUp()			const { return up; }
	const D3DXVECTOR3& GetSide()		const { return side; }

public:
	virtual void Frame();
	virtual void Frame( const D3DXMATRIX& parent );

public:
	void Translate( const D3DXVECTOR3& _v ) { pos += _v; }
	void Translate( float _x, float _y, float _z ) { pos.x += _x; pos.y += _y; pos.z += _z; }
	void TranslateX( float _x ) { pos.x = _x; }
	void TranslateY( float _y ) { pos.y = _y; }
	void TranslateZ( float _z ) { pos.z = _z; }

	void SetPosition( const D3DXVECTOR3& _v ) { pos = _v; }
	void SetPosition( float _x, float _y, float _z ) { pos.x = _x; pos.y = _y; pos.z = _z; }
	void SetPositionX( float _x ) { pos.x = _x; }
	void SetPositionY( float _y ) { pos.y = _y; }
	void SetPositionZ( float _z ) { pos.z = _z; }

	void Scaling( const D3DXVECTOR3& _v ) {	scl += _v; }
	void Scaling( float _x, float _y, float _z ) { scl.x += _x; scl.y += _y; scl.z += _z; }
	void ScalingX( float _x ) { scl.x += _x; }
	void ScalingY( float _y ) { scl.y += _y; }
	void ScalingZ( float _z ) { scl.z += _z; }

	void SetScale( const D3DXVECTOR3& v ) { scl = v; }
	void SetScale( float _x, float _y, float _z ) { scl.x = _x; scl.y = _y; scl.z = _z; }
	void SetScaleX( float _x ) { scl.x = _x; }
	void SetScaleY( float _y ) { scl.y = _y; }
	void SetScaleZ( float _z ) { scl.z = _z; }

	void Rotation( const D3DXQUATERNION& q ) { rot += q; }
	void Rotation( float _x, float _y, float _z, float _w ) { rot.x += _x; rot.y += _y; rot.z += _z; rot.w += _w; }
	void RotationX( float _x ) { rot.x += _x; }
	void RotationY( float _y ) { rot.y += _y; }
	void RotationZ( float _z ) { rot.z += _z; }
	void RotationW( float _w ) { rot.w += _w; }

	void SetRotate( const D3DXQUATERNION& q ) { rot = q; }
	void SetRotate( float _x, float _y, float _z, float _w ) { rot.x = _x; rot.y = _y; rot.z = _z; rot.w = _w; }
	void SetRotateX( float _x ) { rot.x = _x; }
	void SetRotateY( float _y ) { rot.y = _y; }
	void SetRotateZ( float _z ) { rot.z = _z; }
	void SetRotateW( float _w ) { rot.w = _w; }

private:
	D3DXMATRIX worldMatrix;
	D3DXMATRIX localMatrix;
	D3DXMATRIX sclMatrix;
	D3DXMATRIX rotMatrix;
	D3DXMATRIX posMatrix;
	D3DXVECTOR3	look;
	D3DXVECTOR3	up;
	D3DXVECTOR3	side;
	D3DXVECTOR3	scl;
	D3DXQUATERNION rot;
	D3DXVECTOR3	pos;
};

