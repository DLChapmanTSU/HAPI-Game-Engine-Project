#include "Visualisation.h"
#include "Sprite.h"
#include "Vector3.h"

Visualisation::Visualisation(int w, int h)
{
	m_screen = HAPI.GetScreenPointer();
	m_screenWidth = w;
	m_screenHeight = h;
}

void Visualisation::GenerateSprite(std::string d, std::string i, int w, int h, bool t)
{
	m_sprites[i] = std::make_shared<Sprite>(d, w, h, t);
}

void Visualisation::ClearToColour(HAPI_TColour& c, int w, int h)
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

bool Visualisation::RenderTexture(std::shared_ptr<Vector3>& p, std::string n)
{
	if (m_sprites.find(n) == m_sprites.end()) {
		return false;
	}

	//Generic Sprite Rendering Here

	//Creates pointers to the texture and the first pixel in the screen to render to
	int screenPositionToPointTo = (int)((std::roundf(p->GetX()) + std::roundf(p->GetY()) * m_screenWidth) * 4.0f);
	BYTE* screenPointer = m_screen + screenPositionToPointTo;
	BYTE* texturePointer = m_sprites[n]->GetTexturePointer();

	int upperRowsToIgnore{ 0 };
	int lowerRowsToIgnore{ 0 };

	if (screenPositionToPointTo < 0) {
		upperRowsToIgnore = (int)std::roundf(p->GetY());
		upperRowsToIgnore = -(upperRowsToIgnore);
	}

	if (screenPositionToPointTo > ((m_screenWidth * m_screenHeight - (m_sprites[n]->GetTextureHeight() * m_screenWidth)) * 4)) {
		lowerRowsToIgnore = m_sprites[n]->GetTextureHeight() - (m_screenHeight - (int)std::roundf(p->GetY()));

		if (lowerRowsToIgnore > m_sprites[n]->GetTextureHeight()) {
			return true;
		}
	}

	float px = std::roundf(p->GetX());
	int startColumnsToIgnore{ 0 };
	int endColumnsToIgnore{ 0 };

	if (px < 0.0f) {
		if (-px >= m_sprites[n]->GetTextureWidth()) {
			return true;
		}

		startColumnsToIgnore = -(int)px;
	}

	if (px > m_screenWidth - m_sprites[n]->GetTextureWidth()) {
		if (px >= m_screenWidth) {
			return true;
		}

		endColumnsToIgnore = (int)(px + m_sprites[n]->GetTextureWidth()) - m_screenWidth;
	}

	

	//Uses memcpy to blit line by line if there is no transparency and blits pixel by pixel if there is
	if (m_sprites[n]->GetHasTransparency() == false) {

		for (int i = 0; i < m_sprites[n]->GetTextureHeight() - lowerRowsToIgnore; i++)
		{
			if (i >= upperRowsToIgnore) {
				std::memcpy(screenPointer + (size_t)startColumnsToIgnore * 4, texturePointer + (size_t)startColumnsToIgnore * 4, ((size_t)m_sprites[n]->GetTextureWidth() - endColumnsToIgnore - startColumnsToIgnore) * 4);
			}

			texturePointer += (size_t)m_sprites[n]->GetTextureWidth() * 4;

			screenPointer += (size_t)m_screenWidth * 4;
		}
	}
	else {
		//Calculates an offset to add to the pointer when the end of a row is reached
		int lineEndIncrement = (int)(m_screenWidth - m_sprites[n]->GetTextureWidth()) * 4;

		for (int y = 0; y < m_sprites[n]->GetTextureHeight() - lowerRowsToIgnore; y++)
		{
			for (int x = 0; x < m_sprites[n]->GetTextureWidth(); x++)
			{
				if (y >= upperRowsToIgnore && x >= startColumnsToIgnore && x < m_sprites[n]->GetTextureWidth() - endColumnsToIgnore) {
					//Fetches the alpha of the current pixel
					BYTE alpha = texturePointer[3];

					//If the alpha is 0, nothing is rendered and the pointers move to the next pixel
					if (alpha == 0) {
						texturePointer += 4;
						screenPointer += 4;
						continue;
					}

					//Fetches the rgb values
					BYTE red = texturePointer[0];
					BYTE green = texturePointer[1];
					BYTE blue = texturePointer[2];

					//Directly copies the rgb values if the pixel is fully opaque
					if (alpha == 255.0f) {
						screenPointer[0] = red;
						screenPointer[1] = green;
						screenPointer[2] = blue;
					}
					else {
						//Otherwise, a midpoint is found between the rgb of the background pixel and the sprite pixel
						//This midpoint is then rendered on the screen
						float mod = alpha / 255.0f;

						screenPointer[0] = (BYTE)(mod * red + (1.0f - mod) * screenPointer[0]);
						screenPointer[1] = (BYTE)(mod * green + (1.0f - mod) * screenPointer[1]);
						screenPointer[2] = (BYTE)(mod * blue + (1.0f - mod) * screenPointer[2]);
					}
				}

				texturePointer += 4;
				screenPointer += 4;
			}

			screenPointer += lineEndIncrement;
		}
	}
	
	return true;
}

void Visualisation::ClearPointers()
{
	delete[] m_screen;
}
