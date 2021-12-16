#include "Visualisation.h"
#include "Sprite.h"
#include "Vector3.h"
#include "Rectangle.h"

Visualisation::Visualisation(int w, int h)
{
	m_screen = HAPI.GetScreenPointer();
	m_screenWidth = w;
	m_screenHeight = h;
}

void Visualisation::GenerateSprite(std::string d, std::string i, int w, int h, bool t, int aw, int ah, bool a)
{
	m_sprites[i] = std::make_shared<Sprite>(aw, ah, a, d, w, h, t);
}

void Visualisation::ClearToColour(const HAPI_TColour& c, int w, int h)
{
	if (c.red == c.green && c.red == c.blue) {
		memset(m_screen, c.red, (size_t)w * (size_t)h * 4);
	}
	else {
		for (int i = 0; i < w * h; i++)
		{
			int offset{ i * 4 };
			m_screen[offset] = c.red;
			m_screen[offset + 1] = c.green;
			m_screen[offset + 2] = c.blue;
		}
	}
}

bool Visualisation::RenderTexture(const Vector3& p, std::string n, int f)
{
	//Returns an error if the sprite doesn't exist
	if (m_sprites.find(n) == m_sprites.end()) {
		return false;
	}
	else {
		m_sprites[n]->Render(p, f, m_screen, m_screenWidth, m_screenHeight);
		return true;
	}
}

void Visualisation::ClearPointers()
{
	delete[] m_screen;
}
