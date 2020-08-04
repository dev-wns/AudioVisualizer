#pragma once
#include "..\\Component.h"
#include "..\\..\\Resource\Texture.h"

class Material : public Component
{
public:
	Material();;
	virtual ~Material() = default;

public:
	void Init() override;
	void PrevRender() override;
	void Release() override;

public:
	Texture* GetTexture() const { return texture; }
	const D3DXVECTOR4& GetColor() const { return color; }
	ID3D11InputLayout* GetLayout() const { return layout; }
	ID3D11VertexShader* GetVertexShader() const { return vertexShader; }
	ID3D11PixelShader* GetPixelShader() const { return pixelShader; }

public:
	void SetPixel( const std::string& _name );
	void SetVertexShader( const std::string& _name );
	void SetTexture( Texture* tx );
	void SetColor( const D3DXVECTOR4& _color );
	void SetColor( const float& r, const float& g, const float& b, const float a );
	void SetInstanceLayout();

private:
	D3DXVECTOR4 color;
	Texture* texture;
	ID3D11InputLayout* layout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3DBlob* blobVS;
	ID3DBlob* blobPS;
};

