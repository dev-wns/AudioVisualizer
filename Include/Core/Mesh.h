#pragma once
#include "Component.h"
#include "BaseMath.hpp"

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

class Mesh : public Component
{
public:
	Mesh() = default;
	virtual ~Mesh() = default;

public:
	void Init() override;
	void PrevRender() override;
	void PostRender() override;
	void Release() override;

public:
	void UpdateConstantBuffer( const D3DXMATRIX&, const D3DXMATRIX&, const D3DXMATRIX& );
	void Set( const std::vector<PNCT_VERTEX>& _vertices, const std::vector<DWORD>& _indices );
	void UpdateVertex( const std::vector<PNCT_VERTEX>& _vertices );
	void UpdateVertex();
	void PrevRenderInst();

public:
	VSCB& GetVSCB() { return dataVSCB; }
	const UINT GetIndexCount() const { return numIndex; }
	ID3D11Buffer*& GetVertexBuffer() { return vertexBuffer; }
	ID3D11Buffer* GetIndexBuffer() const { return indexBuffer; }
	ID3D11Buffer*& GetConstantBuffer() { return vertexShaderConstantBuffer; }

private:
	std::vector<PNCT_VERTEX> vertices;
	std::vector<DWORD> indices;
	VSCB dataVSCB;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* vertexShaderConstantBuffer;

	UINT numVertex;
	UINT numIndex;
	UINT sizeVertex;
	UINT sizeIndex;
};

