#pragma once
#include <HAPI_lib.h>

#include "Object.h"
#include "CharacterObject.h"

class PlayerObject : public CharacterObject {
private:
	DWORD m_currentTime{ 0 };
	DWORD m_shotTime{ 0 };
	DWORD m_shotCooldown{ 250 };
public:
	PlayerObject(std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0, ObjectTag t = ObjectTag::E_NEUTRAL, bool a = true) : CharacterObject(h, k, x, y, z, m, t, a) {};
	void Update(World& w);
	void CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<CharacterObject>& p);
};