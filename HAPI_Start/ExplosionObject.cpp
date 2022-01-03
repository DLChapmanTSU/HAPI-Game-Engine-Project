#include "ExplosionObject.h"

void ExplosionObject::Update(World& w)
{
	if (m_currentFrame >= m_maxFrame - 1) {
		m_isActive = false;
	}
}

void ExplosionObject::CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::vector<std::shared_ptr<EnemyObject>>& e, std::shared_ptr<PlayerObject>& p, World& w)
{
	//No collisions
}
