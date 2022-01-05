#pragma once
#include "EnemyObject.h"
#include "Vector3.h"

struct LandingSpots {
private:
	HAPISPACE::DWORD m_startTime;
	Vector3 m_landingPosition;
	bool m_hasLanded;

	friend class BossEnemyObject;
};

class BossEnemyObject : public EnemyObject {
private:
	std::vector<LandingSpots> m_spots;
};