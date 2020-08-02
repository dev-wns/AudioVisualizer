#pragma once
#include <tchar.h>
#include <algorithm>

#pragma pack(push, 1)
struct InstanceData
{
	D3DXMATRIX worldMatrix;
	D3DXVECTOR4 color;
};
#pragma pack(pop)

template<typename _Ty>
static void SafeDelete( _Ty*& object )
{
	if ( object == nullptr )
	{
		return;
	}

	delete object;
	object = nullptr;
}

template<typename _Ty>
static void SafeDeleteArray( _Ty*& object )
{
	if ( object == nullptr )
	{
		return;
	}

	delete[] object;
	object = nullptr;
}

template< typename _Ty >
static void SafeRelease( _Ty*& object )
{
	if ( object == nullptr )
	{
		return;
	}

	object->Release();
	object = nullptr;
}