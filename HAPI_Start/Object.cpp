#include "Object.h"
#include "Vector3.h"

#include <HAPI_lib.h>

using namespace HAPISPACE;

Object::Object(HAPI_TColour c, int x, int y, int z)
{
	m_position = std::make_shared<Vector3>(x, y, z);
	m_hue = c;
}

void Object::Render(BYTE*& s, float d, float h, float w)
{
	//Generic Sprite Rendering Here
	BYTE* texture{ nullptr };
	int width{ 64 };
	int height{ 64 };

	if (!HAPI.LoadTexture(m_sprite, &texture, width, height)) {
		//No load
	}

	BYTE* screenPointer = s + (int)(m_position->GetX() + m_position->GetY() * w) * 4;
	BYTE* texturePointer = texture;

	for (size_t i = 0; i < height; i++)
	{
		std::memcpy(screenPointer, texturePointer, (int)width * 4);

		texturePointer += (int)width * 4;

		screenPointer += (int)w * 4;
	}
}

void Object::SetPosition(Vector3& v)
{
	m_position = std::make_shared<Vector3>(v);
}

std::shared_ptr<Vector3>& Object::GetPosition()
{
	return m_position;
}

void Object::Transform(Vector3& v)
{
	Vector3 temp = *m_position;
	temp = temp + v;
	m_position = std::make_shared<Vector3>(temp);
}

void Object::SetHue(HAPI_TColour& c)
{
	m_hue = c;
}

void Star::Render(BYTE*& s, float d, float h, float w)
{
	float cameraX = 0.5f * w;
	float cameraY = 0.5f * h;

	float screenX = ((d * (m_position->GetX() - cameraX)) / (m_position->GetZ() + d)) + cameraX;
	float screenY = ((d * (m_position->GetY() - cameraY)) / (m_position->GetZ() + d)) + cameraY;

	int offset = (int)screenX + (int)screenY * (int)w;

	if (offset < w * h) {
		if ((offset * 4) >= 0 && (offset * 4) < (w * h * 4)) {
			int size = StarSize();

			for (size_t i = 0; i < size; i++)
			{
				for (size_t j = 0; j < size; j++)
				{
					if ((offset + ((int)w * j) + i) * 4 < (w * h * 4)) {
						s[(offset + ((int)w * j) + i) * 4] = m_hue.red;
						s[((offset + ((int)w * j) + i) * 4) + 1] = m_hue.green;
						s[((offset + ((int)w * j) + i) * 4) + 2] = m_hue.blue;
						s[((offset + ((int)w * j) + i) * 4) + 3] = m_hue.alpha;
					}
				}
			}

			/*if (m_position->GetZ() < 250.0f && m_position->GetZ() > 150.0f) {
				s[offset * 4] = 255;
				if ((offset + 1) * 4 < (w * h * 4)) {
					s[(offset + 1) * 4] = 255;
				}
			}
			else if (m_position->GetZ() < 150.0f) {
				s[offset * 4] = 255;
				if ((offset + 1) * 4 < (w * h * 4)) {
					s[(offset + 1) * 4] = 255;
				}

				if ((offset + (int)w) * 4 < (w * h * 4)) {
					s[(offset + (int)w) * 4] = 255;
				}

				if ((offset + (int)w + 1) * 4 < (w * h * 4)) {
					s[(offset + (int)w + 1) * 4] = 255;
				}
			}
			else {
				s[offset * 4] = 255;
			}*/
		}
	}
}

int Star::StarSize()
{
	int size;
	int temp = m_position->GetZ();

	if (temp > 400) {
		size = 1;
	}
	else if (temp <= 400 && temp > 300) {
		size = 2;
	}
	else if (temp <= 300 && temp > 200) {
		size = 3;
	}
	else if (temp <= 200 && temp > 100) {
		size = 4;
	}
	else {
		size = 5;
	}

	return size;
}
