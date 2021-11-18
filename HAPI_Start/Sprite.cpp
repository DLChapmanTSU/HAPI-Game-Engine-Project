#include "Sprite.h"

Sprite::Sprite(int aw, int ah, bool i, std::string s, int w, int h, bool t)
{
	//Constructs the basic elements of the sprite
	//Kills the program if the texture fails to load
	m_textureWidth = w;
	m_textureHeight = h;
	m_hasTransparency = t;
	m_isAnimation = i;

	if (m_isAnimation) {
		m_sheetWidth = aw;
		m_sheetHeight = ah;
	}
	else {
		m_sheetWidth = w;
		m_sheetHeight = h;
		m_currentFrame = 0;
	}

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
	//Increments the animation one frame forward
	//Loops back to the first frame if m_currentFrame grows too big
	//Useful for simple looping animations
	if (m_isAnimation == false) {
		return;
	}

	if (m_currentFrame >= m_frameCount - 1) {
		m_currentFrame = 0;
	}
	else {
		m_currentFrame++;
	}
}

size_t Sprite::GetTextureStepOffset()
{
	if (m_isAnimation) {
		return 0;
	}

	return ((size_t)m_sheetWidth - m_textureWidth) * 4;
}

void Sprite::SetFrame(int i)
{
	//Sets current frame of the animation.
	//Defaults to either 0 or the max frame if the value is too big or small
	if (i >= m_frameCount || i < 0) {
		return;
	}
	else {
		m_currentFrame = i;
	}
}
