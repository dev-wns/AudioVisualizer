#pragma once
#include "Spectrum.h"
#include "ParticleSystem.h"
#include <mutex>
#include "Plane.h"

class SoundPlayer : public GameObject
{
public:
	SoundPlayer( const std::wstring _name, GameObject* _cam, EObject _type ) : GameObject( _name, _cam, _type ) { }
	virtual ~SoundPlayer() = default;

public:
	void Init() override;
	void Frame() override;
	void Render( ID3D11DeviceContext* context ) override;
	void Release() override;

private:
	void BassUpdate();
	void Update();

private:
	bool isCenterBass = true;
	bool isBarBass = true;
	float aroundScale = 175.0f;
	float lengthAmount = 2000.0f;
	float barScale = 1.70f;

	Plane* centerImage;
	float bassPower = 25.0f; // 베이스 증폭 힘
	float bassAmount;         // 현재 베이스 양
	float rawBassValue;       // 베이스 원시값

	Plane* backGround;
	Spectrum* spectrum;
	ParticleSystem* particle;

	bool isCameraShake = true;

	float shakePower = 0.0f;
};

