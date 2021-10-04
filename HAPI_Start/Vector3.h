#pragma once

struct Vector3 {
private:
	float m_x = 0;
	float m_y = 0;
	float m_z = 0;
public:
	Vector3(float x = 0, float y = 0, float z = 0);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	float GetX();
	float GetY();
	float GetZ();
};