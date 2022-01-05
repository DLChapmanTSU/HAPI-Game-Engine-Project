#pragma once
#include <HAPI_lib.h>

#include "Vector3.h"

class Visualisation;

class StatBar {
private:
	Vector3 m_screenPosition;
	float m_maxValue;
	float m_currentValue;
	//std::string m_spriteKey;
	HAPISPACE::HAPI_TColour m_colour;
public:
	StatBar(Vector3& p, float m, HAPISPACE::HAPI_TColour& c);
	void SetValue(unsigned int n);
	void Render(Visualisation& v);
};