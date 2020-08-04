#include "StdAfx.hpp"
#include "Line.h"

Line::Line( const std::wstring& _name, GameObject* _cam, EObject _type ) : GameObject( _name, _cam, _type ) { }

void Line::Init() 
{
	std::vector<PNCT_VERTEX> vertices;
	vertices.resize( 2 );
	vertices[0] = PNCT_VERTEX( D3DXVECTOR3( -1.0f, 1.0f, -1.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 0.0f, 0.0f ) );
	vertices[1] = PNCT_VERTEX( D3DXVECTOR3( 1.0f, 1.0f, -1.0f ), D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 1.0f, 0.0f ) );

	std::vector<DWORD> indices;
	indices.resize( 2 );
	indices[0] = 0; indices[1] = 1;

	GetComponent<Mesh>()->Set( vertices, indices );

	GameObject::Init();
}
void Line::Update( const D3DXVECTOR3& start, const D3DXVECTOR3& end )
{
	std::vector<PNCT_VERTEX> vertices;
	vertices.resize( 2 );
	//D3DXVECTOR3 _start;
	//float nor = ( start.x* start.x + start.y * start.y + start.z * start.z ) / 3.0f;
	//_start.x = start.x / nor;
	//_start.y = start.y / nor;
	//_start.z = start.z / nor;
	vertices[0] = PNCT_VERTEX( start, D3DXVECTOR3( 0.0f, 0.0f, -1.0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 0.0f, 0.0f ) );
	vertices[1] = PNCT_VERTEX( end, D3DXVECTOR3( 0.0f, 0.0f, .0f ), D3DXVECTOR4( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR2( 1.0f, 0.0f ) );
	//std::vector<DWORD> indices;
	//indices.resize( 2 );
	//indices[0] = 0; indices[1] = 1;

	//GetComponent<Mesh>()->Set( vertices, indices );
	GetComponent<Mesh>()->UpdateVertex( vertices );
}