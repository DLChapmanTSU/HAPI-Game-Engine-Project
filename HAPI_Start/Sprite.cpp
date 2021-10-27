#include "Sprite.h"

Sprite::Sprite(std::string s, int w, int h, bool t)
{
	//Constructs the basic elements of the sprite
	//Kills the program if the texture fails to load
	m_textureWidth = w;
	m_textureHeight = h;
	m_hasTransparency = t;
	
	if (!HAPI.LoadTexture(s, &m_texture, w, h)) {
		//No load
		HAPI.UserMessage("Texture Failed To Load", "ERROR");
		HAPI.Close();
	}
}
