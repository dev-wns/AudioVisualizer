#pragma once
#include "Core.h"
#include "Spectrum.h"
#include "ParticleSystem.h"
#include "Plane.h"

class SoundPlayer : public Core
{
public:
	SoundPlayer() = default; // const std::wstring _name, GameObject* _cam, EObject _type ) : GameObject( _name, _cam, _type ) { }
	virtual ~SoundPlayer() = default;

public:
	void Init() override;
	void Frame() override;
	void Release() override;

private:
	void BassUpdate();
	void Update();

private:
	bool isCameraShake = false;
	bool isCenterBass = true;
	bool isBarBass = true;

	float aroundScale = 175.0f;
	float lengthAmount = 2000.0f;
	float barScale = 1.70f;

	float bassPower = 25.0f;  // 베이스 증폭 힘
	float bassAmount;         // 현재 베이스 양
	float rawBassValue;       // 베이스 원시 값

	float shakePower = 5.0f;

	Plane* centerImage;
	Plane* backGround;
	Spectrum* spectrum;
	ParticleSystem* particle;
};

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow )
{
	SoundPlayer player;
	if ( player.SetWindow( hInstance, 2560, 1440, L"Audio Visualizer" ) )
	{
		player.Run();
		return 0;
	}
	return 1;
	hInstance; hPrevInstance; lpCmdLine; lpCmdShow;
}