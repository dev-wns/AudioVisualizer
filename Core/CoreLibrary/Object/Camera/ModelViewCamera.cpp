//#include "..\\..\\Standard\Standard.hpp"
#include "ModelViewCamera.h"


void ModelViewCamera::Create( LONG width, LONG height ) 
{
	::D3DXMatrixLookAtLH( &viewMatrix, &Vector3::Backward, &Vector3::Zero, &Vector3::Up );
	::D3DXMatrixPerspectiveFovLH( &projMatrix,
		static_cast< FLOAT >( D3DX_PI * 0.25f ),
		static_cast< FLOAT >( width / height ), 0.1f, 1000.0f );
}

void ModelViewCamera::CreateViewMatrix() 
{
	::D3DXMatrixLookAtLH( &viewMatrix, &Vector3::Backward, &Vector3::Zero, &Vector3::Up );
}

void ModelViewCamera::CreateProjMatrix( LONG width, LONG height ) 
{
	::D3DXMatrixPerspectiveFovLH( &projMatrix,
		static_cast< FLOAT >( D3DX_PI * 0.25f ),
		static_cast< FLOAT >( width / height ), 0.1f, 1000.0f );
}