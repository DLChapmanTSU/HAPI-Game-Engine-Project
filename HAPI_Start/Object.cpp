#include "Object.h"
#include "Vector3.h"

#include <HAPI_lib.h>

using namespace HAPISPACE;

Object::Object(int x, int y, int z)
{
	m_position = std::make_shared<Vector3>(x, y, z);
}

void Object::Render(BYTE* s, int d)
{
	//BYTE* screen = HAPI.GetScreenPointer();

	int screenX = ((m_position->GetX() - (0)) * d) / ((m_position->GetZ() + d) + (0));
	int screenY = ((m_position->GetY() - (0)) * d) / ((m_position->GetZ() + d) + (0));

	int offset = screenX + screenY * 1024;

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
