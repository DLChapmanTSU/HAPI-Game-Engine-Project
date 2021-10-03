#pragma once

struct Vector3 {
private:
	int m_x = 0;
	int m_y = 0;
	int m_z = 0;
public:
	Vector3(int x = 0, int y = 0, int z = 0);
	void SetX(int x);
	void SetY(int y);
	void SetZ(int z);
	int GetX();
	int GetY();
	int GetZ();
};