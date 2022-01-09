#include "RoamingEnemyObject.h"
#include "World.h"
#include "PlayerObject.h"

RoamingEnemyObject::RoamingEnemyObject(std::pair<int, int> h, std::string k, float x, float y, float z, int m, ObjectTag t, bool a) : EnemyObject(h, k, x, y, z, m, t, a, 10, 6.0f)
{
	//m_health = 10;

	m_targetPositions.push_back(Vector3(200.0f, 200.0f, 0.0f));
	m_targetPositions.push_back(Vector3(824.0f, 200.0f, 0.0f));
	m_targetPositions.push_back(Vector3(824.0f, 568.0f, 0.0f));
	m_targetPositions.push_back(Vector3(200.0f, 569.0f, 0.0f));

	//m_moveSpeed = 1.0f;
}

void RoamingEnemyObject::Update(World& w)
{
	if (m_health <= 0) {
		return;
	}

	HAPISPACE::DWORD currentTime = HAPI.GetTime();

	UpdateState(w.GetPlayerPosition());

	//Shoots if the enemy is within a set radius and patrols between set points if not
	switch (m_currentState)
	{
	case State::E_STATIONARY:
		return;
		break;
	case State::E_ATTACKING:
		if (currentTime - m_shotTime > (DWORD)1000) {
			w.SpawnBullet(*m_position, Vector3(1.0f, 0.0f, 0.0f), ObjectTag::E_ENEMY_BULLET);
			w.SpawnBullet(*m_position, Vector3(-1.0f, 0.0f, 0.0f), ObjectTag::E_ENEMY_BULLET);
			w.SpawnBullet(*m_position, Vector3(0.0f, 1.0f, 0.0f), ObjectTag::E_ENEMY_BULLET);
			w.SpawnBullet(*m_position, Vector3(0.0f, -1.0f, 0.0f), ObjectTag::E_ENEMY_BULLET);
			w.SpawnBullet(*m_position, Vector3(0.5f, 0.5f, 0.0f), ObjectTag::E_ENEMY_BULLET);
			w.SpawnBullet(*m_position, Vector3(-0.5f, 0.5f, 0.0f), ObjectTag::E_ENEMY_BULLET);
			w.SpawnBullet(*m_position, Vector3(0.5f, -0.5f, 0.0f), ObjectTag::E_ENEMY_BULLET);
			w.SpawnBullet(*m_position, Vector3(-0.5f, -0.5f, 0.0f), ObjectTag::E_ENEMY_BULLET);

			m_shotTime = HAPI.GetTime();
		}

		*m_velocity = Vector3(0.0f, 0.0f, 0.0f);
		break;
	case State::E_PATROLLING:
		*m_velocity = m_targetPositions[m_targetIndex] - *m_position;
		break;
	case State::E_CHASING:
		break;
	default:
		break;
	}

	m_velocity->Normalize();

	Translate(*m_velocity * m_moveSpeed);
}

void RoamingEnemyObject::CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<PlayerObject>& p, World& w)
{
	//All other collisions handles what happens when this enemy is hit
}

void RoamingEnemyObject::UpdateState(const Vector3& p)
{
	Vector3 playerPos = p;
	Vector3 targetDifference = m_targetPositions[m_targetIndex] - *m_position;
	Vector3 playerDifference = playerPos - *m_position;

	//Makes the enemy attack if the player is in range and patrol if not
	if (targetDifference.GetX() <= 20.0f && targetDifference.GetX() >= -20.0f && targetDifference.GetY() <= 20.0f && targetDifference.GetY() >= -20.0f) {
		*m_position = m_targetPositions[m_targetIndex];
		m_currentState = State::E_PATROLLING;

		m_targetIndex++;
		if (m_targetIndex >= m_targetPositions.size()) {
			m_targetIndex = 0;
		}
	}
	else {
		m_currentState = State::E_PATROLLING;
	}

	if (playerDifference.GetX() <= 300.0f && playerDifference.GetX() >= -300.0f && playerDifference.GetY() <= 300.0f && playerDifference.GetY() >= -300.0f) {
		m_currentState = State::E_ATTACKING;
	}


}