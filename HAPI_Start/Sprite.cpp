#include "Sprite.h"

Sprite::Sprite(int aw, int ah, bool i, std::string s, int w, int h, bool t)
{
	//Constructs the basic elements of the sprite
	//Kills the program if the texture fails to load
	m_textureWidth = w;
	m_textureHeight = h;
	m_hasTransparency = t;
	m_sheetWidth = aw;
	m_sheetHeight = ah;
	m_isAnimation = i;

	m_frameCount = m_sheetWidth / m_textureWidth;
	
	if (!m_isAnimation) {
		if (!HAPI.LoadTexture(s, &m_texture, w, h)) {
			//No load
			HAPI.UserMessage("Texture Failed To Load", "ERROR");
			HAPI.Close();
		}
	}
	else {
		if (!HAPI.LoadTexture(s, &m_texture, aw, ah)) {
			//No load
			HAPI.UserMessage("Texture Failed To Load", "ERROR");
			HAPI.Close();
		}
	}
	
}

Sprite::~Sprite()
{
	delete[] m_texture;
}

void Sprite::StepAnimation()
{
	if (m_isAnimation == false) {
		return;
	}

	if (m_frameCount == m_currentFrame) {
		m_texture = 0;
	}
	else {
		m_texture += (size_t)m_textureWidth * 4;
	}
}

size_t Sprite::GetTextureStepOffset()
{
	if (m_isAnimation) {
		return 0;
	}

	return ((size_t)m_sheetWidth - m_textureWidth) * 4;
}
