#pragma once
#include "GameObject.h"

class Bar : public GameObject
{
public:
	Bar( const std::wstring& _name, const GameObject* _cam, EObject _oType );
};

class Spectrum : public GameObject
{
public:
	Spectrum( const std::wstring& _name, const GameObject* _cam, EObject _oType, UINT _maxSpectrum );
	virtual ~Spectrum() = default;

public:
	void Init() override;
	void Frame() override;
	void Render( ID3D11DeviceContext* context ) override;
	void Release() override;

public:
	void UpdatePosition( const float& _aroundScale, const float& _bassAmount );
	void UpdateLength( const float& _lengthAmount );

private:
	UINT maxSpectrum;
	std::vector<InstanceData> instanceData;
	ID3D11Buffer* instanceBuffer;
	float barScale;
};

