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
	float xSquared = std::pow(m_x, 2.0f);
	float ySquared = std::pow(m_y, 2.0f);
	float zSquared = std::pow(m_z, 2.0f);
	float squaredLength = xSquared + ySquared + zSquared;

	float length = std::sqrt(squaredLength);

	if (length != 0) {
		m_x /= length;
		//m_x = std::roundf(m_x);

		m_y /= length;
		//m_y = std::roundf(m_y);

		m_z /= length;
		//m_z = std::roundf(m_z);
	}
}
