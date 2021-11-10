#pragma once

#include <HAPI_lib.h>

using namespace HAPISPACE;

class Sprite {
private:
	BYTE* m_texture;
	int m_textureWidth;
	int m_textureHeight;
	bool m_hasTransparency{ false };
	int m_animationOffset{ 0 };
	int m_animationWidth;
	int m_animationHeight;
	bool m_isAnimation{ false };
public:
	Sprite(int aw, int ah, bool i = false, std::string s = "Data\\background.tga", int w = 64, int h = 64, bool t = false);
	~Sprite();
	BYTE*& GetTexturePointer() { return m_texture; };
	int GetTextureWidth() const { return m_textureWidth; };
	int GetTextureHeight() const { return m_textureHeight; };
	bool GetHasTransparency() const { return m_hasTransparency; };
};