#include "Object.h"
#include "Vector3.h"

#include <HAPI_lib.h>

using namespace HAPISPACE;

Object::Object(int x, int y, int z)
{
	m_position = std::make_shared<Vector3>(x, y, z);
}

void Object::Render(BYTE* s, float d)
{
	//BYTE* screen = HAPI.GetScreenPointer();

	float testX = m_position->GetX();
	float testY = m_position->GetY();
	float testZ = m_position->GetZ();

	float screenX = ((d * (m_position->GetX() - 512.0f)) / ((d + m_position->GetZ())) + 512.0f);
	float screenY = ((d * (m_position->GetY() - 384.0f)) / ((d + m_position->GetZ())) + 384.0f);

	int offset = screenY + screenX * 768;

	if (offset >= 0) {
		s[offset * 4] = 255;
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
