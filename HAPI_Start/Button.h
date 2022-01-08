#pragma once
#include <HAPI_lib.h>

#include "Vector3.h"

class Visualisation;

class Button {
private:
	Vector3 m_screenPosition;
	unsigned int m_width;
	unsigned int m_height;
	std::string m_message;
	HAPISPACE::HAPI_TColour m_colour;
	bool m_isActive;
public:
	Button(Vector3& p, unsigned int w, unsigned int h, std::string m = "Text", HAPISPACE::HAPI_TColour c = HAPISPACE::HAPI_TColour::WHITE, bool a = false);
	bool HasClick(Vector3& p);
	void Render(Visualisation& v);
	void SetIsActive(bool a);
};