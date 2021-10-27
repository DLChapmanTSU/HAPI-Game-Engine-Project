#include "Object.h"
#include "Vector3.h"

#include <HAPI_lib.h>

using namespace HAPISPACE;

Object::Object(int x, int y, int z)
{
	m_position = std::make_shared<Vector3>(x, y, z);
	//m_hue = c;
	//m_hasTransparency = t;
	//m_textureWidth = w;
	//m_textureHeight = h;
	//if (!HAPI.LoadTexture(s, &m_texture, w, h)) {
	//	//No load
	//	HAPI.UserMessage("Texture Failed To Load", "ERROR");
	//	HAPI.Close();
	//}
}

//void Object::Render(BYTE*& s, float d, float h, float w)
//{
//	//Generic Sprite Rendering Here
//
//	//Creates pointers to the texture and the first pixel in the screen to render to
//	int screenPositionToPointTo = (int)((std::roundf(m_position->GetX()) + std::roundf(m_position->GetY()) * w) * 4.0f);
//	BYTE* screenPointer = s + screenPositionToPointTo;
//	BYTE* texturePointer = m_texture;
//
//	int upperRowsToIgnore{ 0 };
//	int lowerRowsToIgnore{ 0 };
//
//	if (screenPositionToPointTo < 0) {
//		upperRowsToIgnore = std::roundf(m_position->GetY());
//		upperRowsToIgnore = -(upperRowsToIgnore);
//	}
//
//	if (screenPositionToPointTo > ((w * h - (m_textureHeight * w)) * 4)) {
//		lowerRowsToIgnore = m_textureHeight - (h - std::roundf(m_position->GetY()));
//
//		if (lowerRowsToIgnore > m_textureHeight) {
//			return;
//		}
//	}
//
//	float px = std::roundf(m_position->GetX());
//	int startColumnsToIgnore{ 0 };
//	int endColumnsToIgnore{ 0 };
//
//	if (px < 0.0f) {
//		if (-px >= m_textureWidth) {
//			return;
//		}
//
//		startColumnsToIgnore = -(int)px;
//	}
//
//	if (px > w - m_textureWidth) {
//		if (px >= w) {
//			return;
//		}
//
//		endColumnsToIgnore = (px + m_textureWidth) - w;
//	}
//
//	//Uses memcpy to blit line by line if there is no transparency and blits pixel by pixel if there is
//	if (m_hasTransparency == false) {
//		for (size_t i = 0; i < (size_t)m_textureHeight - (size_t)lowerRowsToIgnore; i++)
//		{
//			if (i >= upperRowsToIgnore) {
//				std::memcpy(screenPointer, texturePointer, (size_t)m_textureWidth * 4);
//			}
//
//			texturePointer += (size_t)m_textureWidth * 4;
//
//			screenPointer += (size_t)w * 4;
//		}
//	}
//	else {
//		//Calculates an offset to add to the pointer when the end of a row is reached
//		int lineEndIncrement = (int)(w - m_textureWidth) * 4.0f;
//
//		for (size_t y = 0; y < (size_t)m_textureHeight - (size_t)lowerRowsToIgnore; y++)
//		{
//			for (size_t x = 0; x < (size_t)m_textureHeight; x++)
//			{
//				if (y >= upperRowsToIgnore && x >= startColumnsToIgnore && x < m_textureWidth - endColumnsToIgnore) {
//					//Fetches the alpha of the current pixel
//					BYTE alpha = texturePointer[3];
//
//					//If the alpha is 0, nothing is rendered and the pointers move to the next pixel
//					if (alpha == 0) {
//						texturePointer += 4;
//						screenPointer += 4;
//						continue;
//					}
//
//					//Fetches the rgb values
//					BYTE red = texturePointer[0];
//					BYTE green = texturePointer[1];
//					BYTE blue = texturePointer[2];
//
//					//Directly copies the rgb values if the pixel is fully opaque
//					if (alpha == 255.0f) {
//						screenPointer[0] = red;
//						screenPointer[1] = green;
//						screenPointer[2] = blue;
//					}
//					else {
//						//Otherwise, a midpoint is found between the rgb of the background pixel and the sprite pixel
//						//This midpoint is then rendered on the screen
//						float mod = alpha / 255.0f;
//
//						screenPointer[0] = (BYTE)(mod * red + (1.0f - mod) * screenPointer[0]);
//						screenPointer[1] = (BYTE)(mod * green + (1.0f - mod) * screenPointer[1]);
//						screenPointer[2] = (BYTE)(mod * blue + (1.0f - mod) * screenPointer[2]);
//					}
//				}
//
//				texturePointer += 4;
//				screenPointer += 4;
//			}
//
//			screenPointer += lineEndIncrement;
//		}
//	}
//}

void Object::SetPosition(Vector3& v)
{
	m_position = std::make_shared<Vector3>(v);
}

std::shared_ptr<Vector3>& Object::GetPosition()
{
	return m_position;
}

void Object::Translate(Vector3& v)
{
	Vector3 temp = *m_position;
	temp = temp + v;
	m_position = std::make_shared<Vector3>(temp);
}

//void Object::SetHue(HAPI_TColour& c)
//{
//	m_hue = c;
//}
//
//void Object::ClearPointers()
//{
//	delete[] m_texture;
//}

//void Star::Render(BYTE*& s, float d, float h, float w)
//{
//	//Unique rendering for the stars
//
//	//Calculates the position of the middle of the screen (where the 'camera' is)
//	float cameraX = 0.5f * w;
//	float cameraY = 0.5f * h;
//
//	//Projection calculation to find where the star should be rendered on the stream
//	float screenX = ((d * (m_position->GetX() - cameraX)) / (m_position->GetZ() + d)) + cameraX;
//	float screenY = ((d * (m_position->GetY() - cameraY)) / (m_position->GetZ() + d)) + cameraY;
//
//	//Calculates a screen offset to find the exact pixel on the screen to be rendered to
//	int offset = (int)screenX + (int)screenY * (int)w;
//
//	//Runs checks to make sure the program isn't going to try and render a pixel not on the screen
//	if (offset < w * h) {
//		//Fetches the stars size which is calculated based on its z value
//		int size = StarSize();
//
//		//If each given pixel is able to be rendered on the screen it is rendered
//		//Pixels that fall outside the bounds of the screen are ignored
//		for (size_t i = 0; i < size; i++)
//		{
//			for (size_t j = 0; j < size; j++)
//			{
//				if ((offset + ((int)w * j) + i) * 4 < (w * h * 4) && screenX + i < w && screenX + i > 0) {
//					s[(offset + ((int)w * j) + i) * 4] = m_hue.red;
//					s[((offset + ((int)w * j) + i) * 4) + 1] = m_hue.green;
//					s[((offset + ((int)w * j) + i) * 4) + 2] = m_hue.blue;
//					s[((offset + ((int)w * j) + i) * 4) + 3] = m_hue.alpha;
//				}
//			}
//		}
//	}
//}
//
//int Star::StarSize()
//{
//	//Grabs the z position and divides it by 100
//	int size;
//	float currentZ = m_position->GetZ();
//	int zDivided = currentZ / 100.0f;
//
//	//Determines the size based on the result of the division
//	switch (zDivided)
//	{
//	case 0:
//		size = 5;
//		break;
//	case 1:
//		size = 4;
//		break;
//	case 2:
//		size = 3;
//		break;
//	case 3:
//		size = 2;
//		break;
//	case 4:
//		size = 1;
//		break;
//	default:
//		size = 1;
//		break;
//	}
//
//	return size;
//}
