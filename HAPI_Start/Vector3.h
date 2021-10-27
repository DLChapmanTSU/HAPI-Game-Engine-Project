#pragma once

class Vector3 {
private:
	float m_x = 0.0f;
	float m_y = 0.0f;
	float m_z = 0.0f;
public:
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	float GetX();
	float GetY();
	float GetZ();
	void Normalize();

	friend Vector3 operator+(Vector3& v1, Vector3& v2);
};

inline Vector3 operator+(Vector3& v1, Vector3& v2) {
	Vector3 result;
	result.m_x = v1.m_x + v2.m_x;
	result.m_y = v1.m_y + v2.m_y;
	result.m_z = v1.m_z + v2.m_z;

	return result;
}