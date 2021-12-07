#pragma once
#include <memory>
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Object;
class CharacterObject;
class Visualisation;
class Vector3;

class World {
private:
	std::vector<std::shared_ptr<Object>> m_worldObjects;
	std::shared_ptr<CharacterObject> m_playerObject;
	std::vector<std::shared_ptr<Object>> m_bulletPool;
	//std::vector<std::shared_ptr<Object>> m_activeBulletPool;
	DWORD m_currentTime;
	DWORD m_lastUpdateTime;
	DWORD m_lastAnimationTime;
public:
	World();
	void Run();
	void SpawnBullet(Vector3& p, Vector3& v);
private:
	void MasterRender(Visualisation& v, float s);
};
