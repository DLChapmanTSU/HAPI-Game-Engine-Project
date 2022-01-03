#pragma once
#include <HAPI_lib.h>

#include "Object.h"
//#include "CharacterObject.h"
#include "Vector3.h"

enum class State {
	E_STATIONARY,
	E_ATTACKING,
	E_PATROLLING,
	E_CHASING
};

class EnemyObject : public Object {
protected:
	State m_currentState{ State::E_STATIONARY };
	std::vector<Vector3> m_targetPositions;
	size_t m_targetIndex{ 0 };
	int m_health{ 1 };
	HAPISPACE::DWORD m_shotTime{ (HAPISPACE::DWORD)0 };
public:
	EnemyObject(std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0, ObjectTag t = ObjectTag::E_ENEMY, bool a = true) : Object(h, k, x, y, z, m, t, a) {};
private:
	virtual void UpdateState(const Vector3& p) = 0;
};