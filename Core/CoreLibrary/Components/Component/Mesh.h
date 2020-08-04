#pragma once
#include "..\\Component.h"
#include "..\\..\\Standard\Base\BaseStruct.hpp"

class Mesh : public Component
{
public:
	Mesh();
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

