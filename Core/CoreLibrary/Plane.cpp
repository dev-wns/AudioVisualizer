#include "StdAfx.hpp"
#include "Plane.h"

Plane::Plane( const std::wstring& _name, const GameObject* _cam, EObject _type ) : GameObject( _name, _cam, _type ) { }

void Plane::Init()
{
	std::vector<PNCT_VERTEX> vertices;
	vertices.resize( 4 );
	vertices[0] = PNCT_VERTEX( D3DXVECTOR3( -1.0f, 1.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 0.0f, 0.0f ) );
	vertices[1] = PNCT_VERTEX( D3DXVECTOR3( 1.0f, 1.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 1.0f, 0.0f ) );
	vertices[2] = PNCT_VERTEX( D3DXVECTOR3( 1.0f, -1.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 1.0f, 1.0f ) );
	vertices[3] = PNCT_VERTEX( D3DXVECTOR3( -1.0f, -1.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 0.0f, 1.0f ) );

	std::vector<DWORD> indices;
	indices.resize( 6 );
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	GetComponent<Mesh>()->Set( vertices, indices );

	GameObject::Init();
}