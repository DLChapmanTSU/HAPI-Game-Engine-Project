#include "DoorObject.h"

Door::Door(std::pair<int, int> h, std::string k, float x, float y, float z, int m, ObjectTag t, bool a) : Object(h, k, x, y, z, m, t, a)
{
	m_tag = ObjectTag::E_DOOR;
}

void Door::Update(World& w)
{
}

void Door::CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<CharacterObject>& p, World& w)
{
}
