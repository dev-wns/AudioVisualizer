#pragma once
//#include "..\\ExternalLibraries\\DirectX11\\Include\\D3DX10math.h"
#include "StdAfx.hpp"

// Math
namespace Matrix
{
	const static D3DXMATRIX Identity = D3DXMATRIX(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 );
}

namespace Quaternion
{
	const static D3DXQUATERNION Zero = D3DXQUATERNION( 0, 0, 0, 0 );
	const static D3DXQUATERNION One = D3DXQUATERNION( 1, 1, 1, 1 );
}

namespace Vector2
{
	const static D3DXVECTOR2 Zero = D3DXVECTOR2( 0, 0 );
	const static D3DXVECTOR2 One = D3DXVECTOR2( 1, 1 );
}

namespace Vector3
{
	const static D3DXVECTOR3 Zero = D3DXVECTOR3( 0, 0, 0 );
	const static D3DXVECTOR3 One = D3DXVECTOR3( 1, 1, 1 );
	const static D3DXVECTOR3 Right = D3DXVECTOR3( 1, 0, 0 );
	const static D3DXVECTOR3 Left = D3DXVECTOR3( -1, 0, 0 );
	const static D3DXVECTOR3 Up = D3DXVECTOR3( 0, 1, 0 );
	const static D3DXVECTOR3 Down = D3DXVECTOR3( 0, -1, 0 );
	const static D3DXVECTOR3 Forward = D3DXVECTOR3( 0, 0, 1 );
	const static D3DXVECTOR3 Backward = D3DXVECTOR3( 0, 0, -1 );
}

namespace Vector4
{
	const static D3DXVECTOR4 Zero = D3DXVECTOR4( 0, 0, 0, 0 );
	const static D3DXVECTOR4 One = D3DXVECTOR4( 1, 1, 1, 1 );
}

namespace Color
{
	const static D3DXVECTOR4 White = D3DXVECTOR4( 1, 1, 1, 1 );
	const static D3DXVECTOR4 Red   = D3DXVECTOR4( 1, 0, 0, 1 );
	const static D3DXVECTOR4 Green = D3DXVECTOR4( 0, 1, 0, 1 );
	const static D3DXVECTOR4 Blue  = D3DXVECTOR4( 0, 0, 1, 1 );
	const static D3DXVECTOR4 Black = D3DXVECTOR4( 0, 0, 0, 1 );
}

// Function

template <typename TYPE>
inline TYPE Minimum( const TYPE& a, const TYPE& b )
{
	return a < b ? a : b;
}

template <typename TYPE>
inline TYPE Maximum( const TYPE& a, const TYPE& b )
{
	return a > b ? a : b;
}
