#pragma once
#include <HAPI_lib.h>

#include "Object.h"

class CharacterObject : public Object {
protected:
	int m_health{ 100 };
public:
	CharacterObject(std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0, ObjectTag t = ObjectTag::E_NEUTRAL, bool a = true) : Object(h, k, x, y, z, m, t, a) {};
	//virtual void Update() = 0;
	//virtual void CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<CharacterObject>& p) = 0;:
	bool TakeDamage(int d = 0);
};
