//#include "..\\..\\Standard\Standard.hpp"
#include "Mesh.h"
#include "..\\..\\Managed\DxManager.h"
#include "..\\..\\Standard\Base\BaseUtility.hpp"

Mesh::Mesh() : numVertex( 0 ), numIndex( 0 ), sizeVertex( 0 ), sizeIndex( 0 ) { }

void Mesh::Set( const std::vector<PNCT_VERTEX>& _vertices, const std::vector<DWORD>& _indices )
{
	vertices.assign( _vertices.cbegin(), _vertices.cend() );
	numVertex = ( UINT )vertices.size();
	sizeVertex = sizeof( PNCT_VERTEX );

	indices.assign( _indices.cbegin(), _indices.cend() );
	numIndex = ( UINT )indices.size();
	sizeIndex = sizeof( DWORD );

	SafeRelease( vertexBuffer );
	vertexBuffer = Utility::Buffer::CreateBuffer( D3D11_BIND_VERTEX_BUFFER, DxManager::Get()->GetDevice(), &vertices.at( 0 ), sizeVertex, numVertex, true );
	//vertexBuffer = Utility::Buffer::CreateVertexBuffer( DxManager::Get()->GetDevice(), &vertices.at( 0 ), sizeVertex, numVertex );

	SafeRelease( indexBuffer );
	//indexBuffer  = Utility::Buffer::CreateIndexBuffer( DxManager::Get()->GetDevice(), &indices.at( 0 ), sizeIndex, numIndex );
	indexBuffer = Utility::Buffer::CreateBuffer( D3D11_BIND_INDEX_BUFFER, DxManager::Get()->GetDevice(), &indices.at( 0 ), sizeIndex, numIndex );
}

//void Mesh::Set( const std::vector<PCT_VERTEX>& _vertices, const std::vector<DWORD>& _indices )
//{
//	verticesPCT.assign( _vertices.cbegin(), _vertices.cend() );
//	numVertex = ( UINT )verticesPCT.size();
//	sizeVertex = sizeof( PCT_VERTEX );
//
//	indices.assign( _indices.cbegin(), _indices.cend() );
//	numIndex = ( UINT )indices.size();
//	sizeIndex = sizeof( DWORD );
//
//	SafeRelease( vertexBuffer );
//	vertexBuffer = Utility::Buffer::CreateBuffer( D3D11_BIND_VERTEX_BUFFER, DxManager::Get()->GetDevice(), &verticesPCT.at( 0 ), sizeVertex, numVertex, true );
//
//	SafeRelease( indexBuffer );
//	indexBuffer = Utility::Buffer::CreateBuffer( D3D11_BIND_INDEX_BUFFER, DxManager::Get()->GetDevice(), &indices.at( 0 ), sizeIndex, numIndex );
//}

void Mesh::UpdateConstantBuffer( const D3DXMATRIX& world, const D3DXMATRIX& view, const D3DXMATRIX& proj )
{
	::D3DXMatrixTranspose( &dataVSCB.world, &world );
	::D3DXMatrixTranspose( &dataVSCB.view, &view );
	::D3DXMatrixTranspose( &dataVSCB.proj, &proj );
	if ( vertexShaderConstantBuffer )
	{
		static D3D11_MAPPED_SUBRESOURCE MappedResource = { 0, };
		// Á¢±ÙÇÏ°í ¼öÁ¤ÇÏ°í Á¢±ÙÇØÁ¦
		DxManager::Get()->GetContext()->Map( vertexShaderConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource );
		VSCB* pInstance( ( VSCB* )MappedResource.pData );		// ¹Ù²Ü °´Ã¼

		::memcpy( pInstance, &dataVSCB, sizeof( VSCB ) );
		DxManager::Get()->GetContext()->Unmap( vertexShaderConstantBuffer, 0 );
		//DxManager::Get()->GetContext()->UpdateSubresource( vertexShaderConstantBuffer, 0, NULL, &dataVSCB, 0, 0 );
	}
}

void Mesh::UpdateVertex( const std::vector<PNCT_VERTEX>& _vertices )
{
	static D3D11_MAPPED_SUBRESOURCE MappedResource = { 0, };
	DxManager::Get()->GetContext()->Map( vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource );
	PNCT_VERTEX* pInstance( ( PNCT_VERTEX* )MappedResource.pData );
	::memcpy( pInstance, &_vertices.at( 0 ), sizeof( PNCT_VERTEX ) * _vertices.size() );
	DxManager::Get()->GetContext()->Unmap( vertexBuffer, 0 );

	//DxManager::Get()->GetContext()->UpdateSubresource( vertexBuffer, 0, NULL, &_vertices.at(0), 0, 0 );
}

void Mesh::UpdateVertex()
{
	static D3D11_MAPPED_SUBRESOURCE MappedResource = { 0, };
	DxManager::Get()->GetContext()->Map( vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource );
	PNCT_VERTEX* pInstance( ( PNCT_VERTEX* )MappedResource.pData );

	::memcpy( pInstance, &vertices.at( 0 ), sizeof( PNCT_VERTEX ) * vertices.size() );
	DxManager::Get()->GetContext()->Unmap( vertexBuffer, 0 );

	//DxManager::Get()->GetContext()->UpdateSubresource( vertexBuffer, 0, NULL, &_vertices.at(0), 0, 0 );
}

//void Mesh::UpdateVertexPCT()
//{
//	static D3D11_MAPPED_SUBRESOURCE MappedResource = { 0, };
//	DxManager::Get()->GetContext()->Map( vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource );
//	PCT_VERTEX* pInstance = ( PCT_VERTEX* )MappedResource.pData;		// ¹Ù²Ü °´Ã¼
//
//	memcpy( pInstance, &verticesPCT.at( 0 ), sizeof( PCT_VERTEX ) * verticesPCT.size() );
//	DxManager::Get()->GetContext()->Unmap( vertexBuffer, 0 );
//}

void Mesh::Init() 
{
	//vertexShaderConstantBuffer = Utility::Buffer::CreateConstantBuffer( DxManager::Get()->GetDevice(), &dataVSCB, sizeof( VSCB ), 1 );
	vertexShaderConstantBuffer = Utility::Buffer::CreateBuffer( D3D11_BIND_CONSTANT_BUFFER, DxManager::Get()->GetDevice(), &dataVSCB, sizeof( VSCB ), 1, true );
}

void Mesh::PrevRender()
{
	if ( vertexBuffer == nullptr || indexBuffer == nullptr || vertexShaderConstantBuffer == nullptr ) return;

	const UINT& stride( sizeVertex );
	const UINT& offset( 0 );

	DxManager::Get()->GetContext()->IASetVertexBuffers( 0, 1, &vertexBuffer, &stride, &offset );
	DxManager::Get()->GetContext()->IASetIndexBuffer( indexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	DxManager::Get()->GetContext()->VSSetConstantBuffers( 0, 1, &vertexShaderConstantBuffer );
	DxManager::Get()->GetContext()->PSSetConstantBuffers( 0, 1, &vertexShaderConstantBuffer );
}

void Mesh::PrevRenderInst()
{
	if ( vertexBuffer == nullptr || indexBuffer == nullptr || vertexShaderConstantBuffer == nullptr ) return;

	DxManager::Get()->GetContext()->IASetIndexBuffer( indexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	DxManager::Get()->GetContext()->VSSetConstantBuffers( 0, 1, &vertexShaderConstantBuffer );
	DxManager::Get()->GetContext()->PSSetConstantBuffers( 0, 1, &vertexShaderConstantBuffer );
}

void Mesh::PostRender()
{
	if ( vertexBuffer == nullptr || indexBuffer == nullptr || vertexShaderConstantBuffer == nullptr ) return;

	DxManager::Get()->GetContext()->DrawIndexed( numIndex, 0, 0 );
}

void Mesh::Release()
{
	vertices.clear();
	indices.clear();

	SafeRelease( vertexBuffer );
	SafeRelease( indexBuffer );
	SafeRelease( vertexShaderConstantBuffer );
}