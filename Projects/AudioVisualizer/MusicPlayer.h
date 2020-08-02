#pragma once
#include "Spectrum.h"
#include "ParticleSystem.h"
#include <mutex>
#include "Plane.h"

class MusicPlayer : public GameObject
{
public:
	MusicPlayer( const std::wstring _name, GameObject* _cam, EObject _type ) : GameObject( _name, _cam, _type ) { }
	virtual ~MusicPlayer() = default;

public:
	void BassUpdate()
	{
		const float& spf( Timer::Get()->SPF() );
		const float* spec( SoundManager::Get()->GetSpectrum()[ESoundCount::S4096L] );
		float calcValue = 0.0f;

		for ( int count = 0; count < 20; count++ )
		{
			calcValue += spec[count];
		}
		rawBassValue = calcValue;
		calcValue *= bassPower;

		if ( bassAmount < calcValue )
			bassAmount = calcValue;

		if ( bassAmount > 0.0f )
			bassAmount -= 500.0f * spf;
		else
			bassAmount = 0.0f;
	}
	void Update()
	{
		BassUpdate();
		if ( isCenterBass == true )
		{
			/*static float maxBass = 0.0f;
			maxBass = bassAmount / 10.0f;
			if ( maxBass >= 1.0f ) 
				maxBass = 1.0f;
			backGround->GetComponent<Mesh>()->GetVSCB().color = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, maxBass );*/
			centerImage->GetComponent<Transform>()->SetScale( aroundScale + bassAmount, aroundScale + bassAmount, 1.0f );
			spectrum->UpdatePosition( aroundScale, bassAmount );
		}
	}
	void Init() override;
	void Frame() override;
	void Render( ID3D11DeviceContext* context ) override;
	// void Release() override;

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

	std::mutex rocker1;
	std::mutex rocker2;

	bool isCameraShake = true;

	float shakePower = 0.0f;
};

