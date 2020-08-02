#pragma once
#include "BaseMath.hpp"

class Particle
{
public:
	Particle() = default;
	virtual ~Particle() = default;

private:
	D3DXVECTOR3 startPos;
	D3DXVECTOR3 endPos;

	D3DXVECTOR3	minScale;
	D3DXVECTOR3	maxScale;

	D3DXQUATERNION mixRotate;
	D3DXQUATERNION maxRotate;

	D3DXVECTOR3	direction;

	float moveSpeed;
	float rotateSpeed;


};

