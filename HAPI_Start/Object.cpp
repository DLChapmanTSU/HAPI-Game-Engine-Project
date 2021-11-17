#include "Object.h"
#include "Vector3.h"

#include <HAPI_lib.h>

using namespace HAPISPACE;

Object::Object(int x, int y, int z, int m)
{
	m_position = std::make_shared<Vector3>(x, y, z);
	m_maxFrame = m;
	//m_spriteName = n;
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

void Object::SetCurrentFrame(int f)
{
	if (f < 0) {
		m_currentFrame = 0;
	}
	else if (f >= m_maxFrame) {
		m_currentFrame = m_maxFrame - 1;
	}
	else {
		m_currentFrame = f;
	}
}
