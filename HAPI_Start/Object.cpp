#include "Object.h"
#include "Vector3.h"

#include <HAPI_lib.h>

using namespace HAPISPACE;

Object::Object(int x, int y, int z)
{
	m_position = std::make_shared<Vector3>(x, y, z);
}

void Object::Render(BYTE* s, float d, float h, float w)
{
	//BYTE* screen = HAPI.GetScreenPointer();

	float testX = m_position->GetX();
	float testY = m_position->GetY();
	float testZ = m_position->GetZ();

	float cameraX = 0.5f * w;
	float cameraY = 0.5f * h;

	float screenX = ((d * (m_position->GetX() - cameraX)) / (m_position->GetZ() + d)) + cameraX;
	float screenY = ((d * (m_position->GetY() - cameraY)) / (m_position->GetZ() + d)) + cameraY;

	if (screenX + screenY < w * h) {
		int offset = screenX + screenY * w;

		if ((offset * 4) >= 0 && (offset * 4) < (w * h * 4)) {
			s[offset * 4] = 255;
		}
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
	//*m_position = *m_position + v;
}
