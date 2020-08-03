#pragma once
#include <map>
#include "Texture.h"
#include "Singleton.hpp"

class TextureManager : public Singleton<TextureManager>
{
public:
	TextureManager() = default;
	virtual ~TextureManager() = default;

public:
	Texture* GetTexture( const std::wstring& _name );
	void AddTexture( const std::wstring& _path );
	void RemoveTexture( const std::wstring& _name );
	void Release();

private:
	friend class Singleton<TextureManager>;
	std::map<std::wstring, Texture*> textures;
};

