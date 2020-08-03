#pragma once
#include "..\\..\\ExternalLibraries\\DirectX11\\Include\\d3dx11.h"

class Texture
{
public:
	Texture() = default;
	virtual ~Texture() = default;

public:
	const std::wstring& GetName() const { return name; }
	const std::wstring& GetPath() const { return path; }
	ID3D11ShaderResourceView*& GetResource() { return resource; }

public:
	void NameDivide( const std::wstring& _path );
	void CreateShaderResourceView( const std::wstring& _path );
	void Release();

private:
	ID3D11ShaderResourceView* resource;
	std::wstring name;
	std::wstring path;
};

