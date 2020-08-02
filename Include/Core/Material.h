#pragma once
#include "Component.h"
#include "Texture.h"

class Material : public Component
{
public:
	Material() = default;
	virtual ~Material() = default;

public:
	void Init() override;
	void PrevRender() override;
	void Release() override;
	void SetPixel( const std::string& _name );
	void SetVertexShader( const std::string& _name );
	void SetTexture( Texture* tx );
	void SetInstanceLayout();
	Texture* GetTexture() const { return texture; }

public:
	Texture* texture;
	ID3D11InputLayout* layout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3DBlob* blobVS;
	ID3DBlob* blobPS;
};

