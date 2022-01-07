#include "BossEnemyObject.h"
#include "Rectangle.h"
#include "Object.h"
#include "PlayerObject.h"
#include "World.h"
#include "Visualisation.h"

BossEnemyObject::BossEnemyObject(std::pair<int, int> h, std::string k, float x, float y, float z, int m, ObjectTag t, bool a) : EnemyObject(h, k, x, y, z, m, t, a, 50, 1.0f)
{
	//m_health = 50;
	m_sprayDirection = Vector3(0.0f, 1.0f, 0.0f);
	m_lastSpray = HAPI.GetTime();

	for (size_t i = 0; i < 5; i++)
	{
		LandingSpots temp;
		temp.m_hasLanded = true;
		temp.m_landingPosition = Vector3(std::rand() % 824 + 100, std::rand() % 568 + 100, 0.0f);
		temp.m_startTime = 0;
		m_spots.push_back(temp);
	}
}

void BossEnemyObject::Update(World& w)
{
	int nextShot = std::rand() % 5;

	if (m_spots[nextShot].m_hasLanded == true) {
		m_spots[nextShot].m_hasLanded = false;
		m_spots[nextShot].m_startTime = HAPI.GetTime();
		m_spots[nextShot].m_landingPosition = Vector3(std::rand() % 824 + 100, std::rand() % 568 + 100, 0.0f);
	}

	UpdateState(w.GetPlayerPosition());

	if (m_currentState == State::E_ATTACKING) {
		DWORD currentTime = HAPI.GetTime();
		
		if (currentTime - m_shotTime >= 100) {
			m_shotTime = currentTime;
			w.SpawnBullet(*m_position, m_sprayDirection, ObjectTag::E_ENEMY_BULLET);

			m_sprayDirection.Rotate(0.0872665f);
		}
	}
}

void BossEnemyObject::CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<PlayerObject>& p, World& w)
{
	if (p->GetIsActive() == true) {
		Rectangle playerHitbox((int)p->GetPosition()->GetX(), (int)p->GetPosition()->GetX() + p->GetHitbox().first, (int)p->GetPosition()->GetY(), (int)p->GetPosition()->GetY() + p->GetHitbox().second);

		for (size_t i = 0; i < 5; i++) {
			DWORD currentTime = HAPI.GetTime();
			DWORD timeElapsed = currentTime - m_spots[i].m_startTime;
			if (timeElapsed >= (DWORD)2000 && m_spots[i].m_hasLanded == false) {
				m_spots[i].m_hasLanded = true;

				w.SpawnExplosion(m_spots[i].m_landingPosition);

				Rectangle shotBox((int)m_spots[i].m_landingPosition.GetX(), (int)m_spots[i].m_landingPosition.GetX() + 64, (int)m_spots[i].m_landingPosition.GetY(), (int)m_spots[i].m_landingPosition.GetY() + 64);

				if (playerHitbox.IsOverlap(shotBox) == true) {
					p->TakeDamage(1);
				}
			}
		}
	}
}

void BossEnemyObject::UpdateState(const Vector3& p)
{
	DWORD currentTime = HAPI.GetTime();
	DWORD timeDiff = currentTime - m_lastSpray;

	if (timeDiff >= (DWORD)10000 && m_currentState == State::E_STATIONARY) {
		m_currentState = State::E_ATTACKING;
		m_lastSpray = HAPI.GetTime();
	}
	else if (timeDiff >= (DWORD)10000 && m_currentState == State::E_ATTACKING) {
		m_currentState = State::E_STATIONARY;
		m_lastSpray = HAPI.GetTime();
	}
}

bool BossEnemyObject::Render(Visualisation& v, float s)
{
	//Won't render if the object is inactive
	if (m_isActive == false) {
		return true;
	}

	//Lerps the object between where it was the previous update and where it will be the next update
	//float fs = (float)s;

	Vector3 lerpPosition;
	lerpPosition.Lerp(*m_position, *m_position + *m_velocity, s);

	const Vector3 lerped = lerpPosition;

	if (!v.RenderTexture(lerped, m_spriteKey, m_currentFrame)) {
		HAPI.UserMessage("Texture Does Not Exist In Visualisation", "ERROR");
		HAPI.Close();
		return false;
	}

	for (size_t i = 0; i < 5; i++)
	{
		if (m_spots[i].m_hasLanded == false) {
			if (!v.RenderTexture(m_spots[i].m_landingPosition, "Target", 0)) {
				HAPI.UserMessage("Texture Does Not Exist In Visualisation", "ERROR");
				HAPI.Close();
				return false;
			}
		}
	}

	return true;
}
