//#include "..\\..\\Standard\Standard.hpp"
#include "UICamera.h"

void UICamera::Create( LONG width, LONG height ) 
{
	::D3DXMatrixLookAtLH( &viewMatrix, &Vector3::Backward, &Vector3::Zero, &Vector3::Up );
	::D3DXMatrixOrthoOffCenterLH( &projMatrix, -width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, 0.0f, 1000.0f );
}

void UICamera::CreateViewMatrix() 
{
	::D3DXMatrixLookAtLH( &viewMatrix, &Vector3::Backward, &Vector3::Zero, &Vector3::Up );
}

void UICamera::CreateProjMatrix( LONG width, LONG height ) 
{
	::D3DXMatrixOrthoOffCenterLH( &projMatrix, -width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, 0.0f, 1000.0f );
}

void UICamera::Frame() 
{
	viewMatrix._41 = GetComponent<Transform>()->GetPosition().x;
	viewMatrix._42 = GetComponent<Transform>()->GetPosition().y;

	GameObject::Frame();
}