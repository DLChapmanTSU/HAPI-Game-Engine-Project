#pragma once

#include <HAPI_lib.h>

using namespace HAPISPACE;

class Sprite {
private:
	BYTE* m_texture;
	int m_textureWidth;
	int m_textureHeight;
	bool m_hasTransparency{ false };
	int m_sheetWidth;
	int m_sheetHeight;
	//std::pair<int, int> m_spriteOffset;
	bool m_isAnimation{ false };
	int m_frameCount;
	int m_currentFrame{ 0 };
public:
	Sprite(int aw, int ah, bool i = false, std::string s = "Data\\background.tga", int w = 64, int h = 64, bool t = false);
	~Sprite();
	BYTE*& GetTexturePointer() { return m_texture; };
	int GetTextureWidth() const { return m_textureWidth; };
	int GetTextureHeight() const { return m_textureHeight; };
	int GetSheetWidth() const { return m_sheetWidth; };
	int GetSheetHeight() const { return m_sheetHeight; };
	bool GetHasTransparency() const { return m_hasTransparency; };
	bool GetIsAnimation() const { return m_isAnimation; };
	int GetCurrentFrame() const { return m_currentFrame; };
	void StepAnimation();
	size_t GetTextureStepOffset();
	void SetFrame(int i);
};