#pragma once
#include <memory>
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Object;
class PlayerObject;
class Visualisation;
class Vector3;
class Map;
class DoorObject;
class EnemyObject;
class Audio;
class StatBar;

enum class DoorDirection;
enum class ObjectTag;

class World {
private:
	std::vector<std::shared_ptr<Object>> m_worldObjects;
	std::shared_ptr<PlayerObject> m_playerObject;
	std::vector<std::shared_ptr<Object>> m_bulletPool;
	std::vector<std::shared_ptr<Object>> m_explosionPool;
	std::vector<std::shared_ptr<EnemyObject>> m_enemyPool;
	//std::vector<std::shared_ptr<Object>> m_activeBulletPool;
	DWORD m_currentTime;
	DWORD m_lastUpdateTime;
	DWORD m_lastAnimationTime;
	std::shared_ptr<Map> m_map;
	std::shared_ptr<Audio> m_audio;
	std::shared_ptr<StatBar> m_playerHealthBar;
public:
	World();
	void Run();
	void SpawnBullet(Vector3& p, Vector3& v, ObjectTag& t);
	void SpawnExplosion(const Vector3& p);
	void MoveRoom(DoorDirection& d);
	const Vector3& GetEnemyPosition(size_t i);
	void SetAIVelocity(size_t i, Vector3& v);
	const Vector3& GetPlayerPosition();
private:
	void MasterRender(Visualisation& v, float s);
	bool CheckAllEnemiesDead();
	void SpawnEnemies();
};
