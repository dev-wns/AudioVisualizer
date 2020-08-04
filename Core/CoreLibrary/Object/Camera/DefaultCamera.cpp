//#include "..\\..\\Standard\Standard.hpp"
#include "DefaultCamera.h"

void DefaultCamera::Create( LONG width, LONG height ) 
{
	::D3DXMatrixLookAtLH( &viewMatrix, &Vector3::Backward, &Vector3::Zero, &Vector3::Up );
	::D3DXMatrixPerspectiveFovLH( &projMatrix,
		static_cast< FLOAT >( D3DX_PI * 0.25f ),
		static_cast< FLOAT >( width / height ), 0.1f, 10000.0f );
}

void DefaultCamera::CreateProjMatrix( LONG width, LONG height ) 
{
	::D3DXMatrixPerspectiveFovLH( &projMatrix,
		static_cast< FLOAT >( D3DX_PI * 0.25f ),
		static_cast< FLOAT >( width / height ), 0.1f, 10000.0f );
}

void DefaultCamera::CreateViewMatrix() 
{
	::D3DXMatrixLookAtLH( &viewMatrix, &Vector3::Backward, &Vector3::Zero, &Vector3::Up );
}