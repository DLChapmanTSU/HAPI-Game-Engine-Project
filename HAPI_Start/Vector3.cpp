#include "Vector3.h"

#include <cmath>

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

void Vector3::Normalize()
{
	float squaredLength = (m_x * m_x) + (m_y * m_y) + (m_z + m_z);

	float length = std::sqrt(squaredLength);

	if (m_x != 0) {
		m_x /= length;
		m_x = std::roundf(m_x);
	}

	if (m_y != 0) {
		m_y /= length;
		m_y = std::roundf(m_y);
	}

	if (m_z != 0) {
		m_z /= length;
		m_z = std::roundf(m_z);
	}
}
