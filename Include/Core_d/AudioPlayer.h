#pragma once
#include "Spectrum.h"
#include "ParticleSystem.h"
#include <mutex>
#include "Plane.h"

class AudioPlayer : public GameObject
{

public:
	AudioPlayer( const std::wstring _name, GameObject* _cam, EObject _type ) : GameObject( _name, _cam, _type ) { }
	virtual ~AudioPlayer() = default;

public:
	void Init() override;
	void Frame() override;
	void Render( ID3D11DeviceContext* context ) override;
	// void Release() override;

private:
	Plane* backGround;
	Spectrum* spectrum;
	ParticleSystem* particle;

	std::mutex rocker1;
	std::mutex rocker2;

	bool isCameraShake = true;

	float shakePower = 0.0f;
};

