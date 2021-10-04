#include "Vector3.h"

Vector3::Vector3(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

void Vector3::SetX(float x)
{
	m_x = x;
}

void Vector3::SetY(float y)
{
	m_y = y;
}

void Vector3::SetZ(float z)
{
	m_z = z;
}

float Vector3::GetX()
{
	return m_x;
}

float Vector3::GetY()
{
	return m_y;
}

float Vector3::GetZ()
{
	return m_z;
}
