#pragma once
#include <HAPI_lib.h>

#include "Object.h"
#include "EnvironmentObject.h"

enum class DoorDirection{
	E_UP,
	E_DOWN,
	E_LEFT,
	E_RIGHT
};

class DoorObject : public EnvironmentObject {
private:
	DoorDirection m_direction;
public:
	DoorObject(DoorDirection d, std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0, ObjectTag t = ObjectTag::E_NEUTRAL, bool a = true);
	void Update(World& w);
	void CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<PlayerObject>& p, World& w);
	~DoorObject();
};