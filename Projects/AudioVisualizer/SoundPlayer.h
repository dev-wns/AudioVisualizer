#pragma once
#include "Core.h"
#include "Spectrum.h"
#include "ParticleSystem.h"
#include "Plane.h"


class SoundPlayer : public Core
{
public:
	SoundPlayer();
	virtual ~SoundPlayer() = default;

public:
	void Init() override;
	void Frame() override;
	void Release() override;

private:
	void BassUpdate();
	void Update();

private:
	bool bBackGroundVisible;
	bool bCenterImageVisible;
	bool bCameraShake;
	bool bCenterBass;
	bool bBarBass;

	float aroundScale;
	float lengthAmount;

	float bassPower;    // ���̽� ���� ��
	float bassAmount;   // ���� ���̽� ��
	float rawBassValue; // ���̽� ���� ��

	float shakePower;

	Plane* centerImage;
	Plane* backGround;
	Spectrum* spectrum;
	ParticleSystem* particle;
};

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow )
{
	SoundPlayer player;
	if ( player.SetWindow( hInstance, L"Audio Visualizer" ) )
	{
		player.Run();
		//::_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
		//::_CrtDumpMemoryLeaks();
		return 0;
	}
	return 1;
	hInstance; hPrevInstance; lpCmdLine; lpCmdShow;
}