#include "Object.h"
#include "Vector3.h"

#include <HAPI_lib.h>

using namespace HAPISPACE;

Object::Object(int x, int y, int z, int sx, int sy)
{
	m_position = std::make_shared<Vector3>(x, y, z);
	m_sizeX = sx;
	m_sizeY = sy;
}

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

std::pair<int, int> Object::GetDimensions() const
{
	return std::pair<int, int>(m_sizeX, m_sizeY);
}
