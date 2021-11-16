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

	Rectangle screenRect(0, m_screenWidth, 0, m_screenHeight);
	Rectangle textureRect(0, m_sprites[n]->GetTextureWidth(), 0, m_sprites[n]->GetTextureHeight());
	textureRect.Translate(*p);
	Rectangle clippedRect = textureRect;
	//clippedRect.Translate(*p);
	clippedRect.Clip(screenRect);
	Vector3 invertedP = *p;
	invertedP.Invert();
	//invertedP.SetX(invertedP.GetX());
	//invertedP.SetY(invertedP.GetY());
	clippedRect.Translate(invertedP);
	/*int frame = m_sprites[n]->GetCurrentFrame();
	Vector3 frameOffset(frame * m_sprites[n]->GetTextureWidth(), 0.0f, 0.0f);
	clippedRect.Translate(frameOffset);*/

	//TRANSFORM CLIPPED RECTANGLE BASED ON CURRENT SPRITE IN ANIMATION

	//Generic Sprite Rendering Here

	//Creates pointers to the texture and the first pixel in the screen to render to
	int screenPositionToPointTo = (int)((std::roundf(p->GetX()) + std::roundf(p->GetY()) * m_screenWidth) * 4.0f);
	BYTE* screenPointer = m_screen + screenPositionToPointTo;
	BYTE* texturePointer = m_sprites[n]->GetTexturePointer();

	//Uses memcpy to blit line by line if there is no transparency and blits pixel by pixel if there is
	if (m_sprites[n]->GetHasTransparency() == false) {
		if (clippedRect.m_right - clippedRect.m_left > 0) {
			//Need to get the difference between the clipped rect and the actual width of the sprite
		//Use that as offset for the memcpy
			int startOffset = (m_screenWidth * clippedRect.m_top) * 4;
			int endOffset = (m_sprites[n]->GetTextureWidth() - (textureRect.m_right - clippedRect.m_right)) * 4;
			screenPointer += (size_t)startOffset;
			texturePointer += (size_t)clippedRect.m_top * m_sprites[n]->GetTextureWidth() * 4;
			screenPointer += (size_t)clippedRect.m_left * 4;
			texturePointer += (size_t)clippedRect.m_left * 4;
			for (int i = clippedRect.m_top; i < clippedRect.m_bottom; i++)
			{
				std::memcpy(screenPointer, texturePointer, ((size_t)clippedRect.m_right - clippedRect.m_left) * 4);

				if (m_sprites[n]->GetIsAnimation() == true) {
					texturePointer += ((size_t)m_sprites[n]->GetSheetWidth() - m_sprites[n]->GetTextureWidth()) * 4;
				}
				else {
					texturePointer += (size_t)m_sprites[n]->GetTextureWidth() * 4;
				}



				screenPointer += (size_t)m_screenWidth * 4;
			}
		}
	}
	else {
		//Calculates an offset to add to the pointer when the end of a row is reached
		int lineEndIncrement = (int)(m_screenWidth - m_sprites[n]->GetTextureWidth()) * 4;
		screenPointer += (size_t)clippedRect.m_top * m_screenWidth * 4;
		texturePointer += (size_t)clippedRect.m_top * m_sprites[n]->GetTextureWidth() * 4;
		screenPointer += (size_t)clippedRect.m_left * 4;
		texturePointer += (size_t)clippedRect.m_left * 4;
		texturePointer += ((size_t)m_sprites[n]->GetCurrentFrame() * m_sprites[n]->GetTextureWidth()) * 4;

		for (int y = clippedRect.m_top; y < clippedRect.m_bottom; y++)
		{
			for (int x = clippedRect.m_left; x < clippedRect.m_right; x++)
			{
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

				texturePointer += 4;
				screenPointer += 4;
			}

			if (m_sprites[n]->GetIsAnimation() == true) {
				texturePointer += ((size_t)m_sprites[n]->GetSheetWidth() - m_sprites[n]->GetTextureWidth()) * 4;
			}

			screenPointer += (size_t)lineEndIncrement;
			screenPointer += (size_t)clippedRect.m_left * 4;
			texturePointer += (size_t)clippedRect.m_left * 4;

			

			int widthDiff = m_sprites[n]->GetTextureWidth() - clippedRect.m_right;
			screenPointer += (size_t)widthDiff * 4;
			texturePointer += (size_t)widthDiff * 4;
		}
	}

	m_sprites[n]->StepAnimation();
	
	return true;
}

void Visualisation::ClearPointers()
{
	delete[] m_screen;
}
