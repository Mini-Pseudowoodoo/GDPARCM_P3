#pragma once
#include "ResourceManager.h"

class TextureManager : public ResourceManager
{
public:
	TextureManager();
	~TextureManager();
	class Texture* CreateTextureFromFile(const wchar_t* file_path); 
protected:
	// Inherited via ResourceManager
	virtual Resource* CreateResourceFromFileConcerete(const wchar_t* file_path) override;
};

