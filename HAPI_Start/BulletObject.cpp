#include "BulletObject.h"
#include "PlayerObject.h"
#include "EnemyObject.h"
#include "Vector3.h"
#include "Rectangle.h"
#include "Visualisation.h"
#include "World.h"

void BulletObject::Update(World& w)
{
	if (m_lifeTime >= 10.0f) {
		m_lifeTime = 0.0f;
		m_isActive = false;
		return;
	}

	//Update position
	Translate(*m_velocity * m_moveSpeed);

	m_lifeTime += 0.1f;

	//m_moveSpeed = 7.0f;
	//m_health = 1;
}

void BulletObject::CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<PlayerObject>& p, World& w)
{
	//Checks for any collisions using rectangles
	//Handles killing itself and damaging characters with a different tag
	Rectangle myHitbox((int)m_position->GetX(), (int)m_position->GetX() + m_hitboxDimensions.first, (int)m_position->GetY(), (int)m_position->GetY() + m_hitboxDimensions.second);

	for (std::shared_ptr<Object> object : o) {
		Rectangle otherHitbox((int)object->GetPosition()->GetX(), (int)object->GetPosition()->GetX() + object->GetHitbox().first, (int)object->GetPosition()->GetY(), (int)object->GetPosition()->GetY() + object->GetHitbox().second);

		if (myHitbox.IsOverlap(otherHitbox) == true && object->GetTag() == ObjectTag::E_ENEMY && m_tag == ObjectTag::E_FRIENDLY_BULLET && object->GetIsActive() == true) {
			//std::cout << "Collision" << std::endl;
			//object->TakeDamage(1);
			if (object->GetTag() == ObjectTag::E_ENEMY) {
				std::shared_ptr<EnemyObject> enemy = std::dynamic_pointer_cast<EnemyObject, Object>(object);
				bool isDead = enemy->TakeDamage(1);

				if (isDead == true) {
					w.SpawnExplosion(*enemy->GetPosition());
				}
			}

			m_isActive = false;
			return;
		}
	}

	if (m_tag != ObjectTag::E_FRIENDLY_BULLET) {
		Rectangle otherHitbox((int)p->GetPosition()->GetX(), (int)p->GetPosition()->GetX() + p->GetHitbox().first, (int)p->GetPosition()->GetY(), (int)p->GetPosition()->GetY() + p->GetHitbox().second);

		if (myHitbox.IsOverlap(otherHitbox) == true && p->GetIsActive() == true) {
			//std::cout << "Character Hit" << std::endl;
			m_isActive = false;
			bool isDead = p->TakeDamage(1);
			if (isDead == true) {
				w.SpawnExplosion(*p->GetPosition());
			}
			//p->TakeDamage(1);
		}
	}
	//else {
	//	for (std::shared_ptr<EnemyObject> enemy : e) {
	//		Rectangle otherHitbox((int)enemy->GetPosition()->GetX(), (int)enemy->GetPosition()->GetX() + enemy->GetHitbox().first, (int)enemy->GetPosition()->GetY(), (int)enemy->GetPosition()->GetY() + enemy->GetHitbox().second);

	//		if (myHitbox.IsOverlap(otherHitbox) == true && enemy->GetIsActive() == true) {
	//			//std::cout << "Character Hit" << std::endl;
	//			m_isActive = false;
	//			bool isDead = enemy->TakeDamage(1);
	//			if (isDead == true) {
	//				w.SpawnExplosion(*enemy->GetPosition());
	//			}
	//			//p->TakeDamage(1);
	//		}
	//	}
	//}
}

void BulletObject::ResetTimer()
{
	m_lifeTime = 0.0f;
}
