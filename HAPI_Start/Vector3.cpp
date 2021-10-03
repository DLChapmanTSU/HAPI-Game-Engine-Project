#include "Vector3.h"

Vector3::Vector3(int x, int y, int z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

void Vector3::SetX(int x)
{
	m_x = x;
}

void Vector3::SetY(int y)
{
	m_y = y;
}

void Vector3::SetZ(int z)
{
	m_z = z;
}

int Vector3::GetX()
{
	return m_x;
}

int Vector3::GetY()
{
	return m_y;
}

int Vector3::GetZ()
{
	return m_z;
}
