#pragma once
#include "GameObject.h"

class Particle : public GameObject
{
public:
	Particle( const std::wstring _name, const GameObject* _cam, EObject _type, bool* _isRainbow );
	virtual ~Particle() = default;

public:
	void Init() override;
	void Frame() override;

private:
	friend class ParticleSystem;
	bool& bRainbow;
	D3DXVECTOR4 defaultColor;
	D3DXVECTOR4 rainbowColor;

	D3DXVECTOR3 startPos;
	D3DXVECTOR3	direction;

	float moveSpeed;
	float respawnDelay;
	float timer;
};

class ParticleSystem : public GameObject
{
public:
	ParticleSystem( const std::wstring _name, const GameObject* _cam, EObject _type, UINT _maxParticle );
	virtual ~ParticleSystem() = default;

public:
	void Init() override;
	void Frame() override;
	void Render( ID3D11DeviceContext* context ) override;
	void Release() override;

private:
	std::vector<InstanceData> instanceData;
	ID3D11Buffer* instanceBuffer;
	bool bRainbow;
	UINT maxParticle;
};