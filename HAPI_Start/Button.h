#pragma once
#include <HAPI_lib.h>

#include "Vector3.h"

class Button {
private:
	Vector3 m_screenPosition;
	unsigned int m_width;
	unsigned int m_height;
public:
	Button(Vector3& p, unsigned int w, unsigned int h);
	bool HasClick(Vector3& p);
};