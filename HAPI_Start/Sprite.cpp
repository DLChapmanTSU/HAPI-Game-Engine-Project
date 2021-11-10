#include "Sprite.h"

Sprite::Sprite(int aw, int ah, bool i, std::string s, int w, int h, bool t)
{
	//Constructs the basic elements of the sprite
	//Kills the program if the texture fails to load
	m_textureWidth = w;
	m_textureHeight = h;
	m_hasTransparency = t;
	m_animationWidth = aw;
	m_animationHeight = ah;
	m_isAnimation = i;
	
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
