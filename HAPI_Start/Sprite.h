#pragma once

#include <HAPI_lib.h>

using namespace HAPISPACE;

class Sprite {
private:
	BYTE* m_texture;
	int m_textureWidth;
	int m_textureHeight;
	bool m_hasTransparency{ false };
public:
	Sprite(std::string s = "Data\\background.tga", int w = 64, int h = 64, bool t = false);
	BYTE*& GetTexturePointer() { return m_texture; };
	int GetTextureWidth() { return m_textureWidth; };
	int GetTextureHeight() { return m_textureHeight; };
	bool GetHasTransparency() { return m_hasTransparency; };
};