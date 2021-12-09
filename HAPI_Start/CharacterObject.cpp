#include "CharacterObject.h"

bool CharacterObject::TakeDamage(int d)
{
	//Reduces the players health and sets to inactive if health reaches 0
	m_health -= d;

	if (m_health <= 0) {
		m_isActive = false;
		return true;
	}
	return false;
}
