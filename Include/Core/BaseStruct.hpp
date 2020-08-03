#pragma once
#include "StdAfx.hpp"
#include "BaseConst.hpp"

#pragma pack(push, 1)
struct InstanceData
{
	D3DXMATRIX worldMatrix;
	D3DXVECTOR4 color;
};
#pragma pack(pop)

struct PNCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;

	PNCT_VERTEX( const D3DXVECTOR3& _p, const D3DXVECTOR3& _n, const D3DXVECTOR4& _c, const D3DXVECTOR2& _t ) : p( _p ), n( _n ), c( _c ), t( _t ) {}
	PNCT_VERTEX() : p( Vector3::Zero ), n( Vector3::Zero ), c( Vector4::Zero ), t( Vector2::Zero ) {}

};

struct VSCB
{
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX proj;
	D3DXVECTOR4 color;

	VSCB() : world( Matrix::Identity ), view( Matrix::Identity ), proj( Matrix::Identity ), color( Vector4::One ) {}
};