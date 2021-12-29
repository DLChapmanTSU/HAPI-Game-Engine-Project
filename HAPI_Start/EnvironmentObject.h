#pragma once
#include <HAPI_lib.h>

#include "Object.h"

class EnvironmentObject : public Object {
public:
	EnvironmentObject(std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0, ObjectTag t = ObjectTag::E_NEUTRAL, bool a = true) : Object(h, k, x, y, z, m, t, a) {};
};