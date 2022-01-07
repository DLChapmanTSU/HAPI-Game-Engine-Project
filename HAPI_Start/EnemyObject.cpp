#include "EnemyObject.h"

EnemyObject::EnemyObject(std::pair<int, int> h, std::string k, float x, float y, float z, int m, ObjectTag t, bool a, unsigned int health, float s) : Object(h, k, x, y, z, m, t, a, s) {
	m_health = health;
	m_maxHealth = m_health;
}

bool EnemyObject::TakeDamage(unsigned int d)
{
	m_health -= d;

	if (m_health <= 0) {
		m_isActive = false;
		return true;
	}

	return false;
}

void EnemyObject::Reset()
{
	m_health = m_maxHealth;
	m_shotTime = HAPI.GetTime();
}
