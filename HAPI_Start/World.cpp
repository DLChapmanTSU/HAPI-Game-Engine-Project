#include "World.h"
#include "Object.h"
#include "Vector3.h"
#include "Visualisation.h"
#include "PlayerObject.h"
#include "BulletObject.h"
#include "WallObject.h"
#include "EnvironmentObject.h"
#include "DoorObject.h"
#include "Map.h"
#include "Room.h"
#include "EnemyObject.h"
#include "RoamingEnemyObject.h"
#include "ChasingEnemyObject.h"
#include "ExplosionObject.h"
#include "Audio.h"

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>

#include <memory>
#include <random>

World::World()
{
	//Create Player
	m_playerObject = std::make_shared<PlayerObject>(std::pair<int, int>(64, 64), "Player", 301.0f, 301.0f, 0.0f, 0, ObjectTag::E_FRIENDLY, true);
	//Create Doors
	m_worldObjects.push_back(std::make_shared<DoorObject>(DoorDirection::E_UP, std::pair<int, int>(64, 64), "Door", 480.0f, 32.0f, 0.0f, 0, ObjectTag::E_DOOR, true));
	m_worldObjects.push_back(std::make_shared<DoorObject>(DoorDirection::E_DOWN, std::pair<int, int>(64, 64), "Door", 480.0f, 672.0f, 0.0f, 0, ObjectTag::E_DOOR, true));
	m_worldObjects.push_back(std::make_shared<DoorObject>(DoorDirection::E_LEFT, std::pair<int, int>(64, 64), "Door", 32.0f, 384.0f, 0.0f, 0, ObjectTag::E_DOOR, true));
	m_worldObjects.push_back(std::make_shared<DoorObject>(DoorDirection::E_RIGHT, std::pair<int, int>(64, 64), "Door", 928.0f, 384.0f, 0.0f, 0, ObjectTag::E_DOOR, true));
	//Create world objects for game
	/*m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(256, 256), "Background", 100.0f, 100.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 200.0f, 100.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 200.0f, 500.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 290.0f, 180.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 750.0f, 100.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 0.0f, 0.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 300.0f, 300.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 200.0f, 600.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 300.0f, 100.0f, 0.0f, 4));*/

	for (size_t i = 0; i < 100; i++)
	{
		m_bulletPool.push_back(std::make_shared<BulletObject>(std::pair<int, int>(32, 32), "Bullet", 0.0f, 0.0f, 0.0f, 0, ObjectTag::E_FRIENDLY, false));
		m_bulletPool.push_back(std::make_shared<BulletObject>(std::pair<int, int>(32, 32), "Bullet", 0.0f, 0.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	}

	for (size_t i = 0; i < 20; i++)
	{
		m_explosionPool.push_back(std::make_shared<ExplosionObject>(std::pair<int, int>(64, 64), "Test", 300.0f, 100.0f, 0.0f, 4, ObjectTag::E_NEUTRAL, false));
	}

	m_currentTime = HAPI.GetTime();
	m_lastUpdateTime = HAPI.GetTime();
	m_lastAnimationTime = HAPI.GetTime();

	Map myMap;
	//myMap.GenerateMap();
	//std::cout << "Generation Attempted" << std::endl;

	m_map = std::make_shared<Map>(myMap);
	//m_map->GenerateMap();

	m_enemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_audio = std::make_shared<Audio>(Audio());
}

void World::Run()
{
	//Initialize screen dimensions and eyes distance from the screen
	int width{ 1024 };
	int height{ 768 };

	m_map->GenerateMap();

	if (!HAPI.Initialise(width, height, "HAPI_Screen"))
		return;

	BYTE* screen = HAPI.GetScreenPointer();

	Visualisation vis(width, height);
	vis.GenerateSprite("Data\\playerSprite.tga", "Player", 64, 64, true, 64, 64, false);
	vis.GenerateSprite("Data\\shapeTest.png", "Test", 64, 64, true, 256, 64, true);
	vis.GenerateSprite("Data\\background.tga", "Background", 256, 256, false, 256, 256, false);
	vis.GenerateSprite("Data\\Bullet.png", "Bullet", 32, 32, true, 32, 32, false);
	vis.GenerateSprite("Data\\Door.png", "Door", 64, 64, true, 64, 64, false);
	vis.GenerateSprite("Data\\RoamingEnemy.png", "RoamingEnemy", 64, 64, true, 64, 64, false);
	vis.GenerateSprite("Data\\ChasingEnemy.png", "ChasingEnemy", 64, 64, true, 64, 64, false);

	//Audio aud;
	//m_audio = aud;
	m_audio->LoadSound("Data\\Audio\\shoot.wav", "Shoot", false, 0.0f, 1.0f, 0.1f);
	m_audio->LoadSound("Data\\Audio\\explosion.wav", "Explosion", false, 0.0f, 1.0f, 1.0f);

	HAPI.SetShowFPS(true);
	HAPI.LimitFrameRate(60);

	SpawnEnemies();



	while (HAPI.Update()) {
		//Clears screen to given colour
		HAPI_TColour bgColour(10, 56, 33, 255);
		vis.ClearToColour(m_map->GetCurrentRoom().GetColour(), 1024, 768);

		

		/*if (keyData.scanCode[HK_SPACE]) {
			for (std::shared_ptr<Object> o : m_bulletPool) {
				if (o->GetIsActive() == false && o->GetTag() == ObjectTag::E_FRIENDLY) {
					o->SetActive(true);
					Vector3 spawnPos = *m_playerObject->GetPosition();
					spawnPos.SetX(spawnPos.GetX() + 16.0f);
					o->SetPosition(spawnPos);
					o->SetVelocity(Vector3(0.0f, -1.0f, 0.0f));
					break;
				}
			}
		}*/

		

		//Check collisions between each object
		m_playerObject->CheckCollision(m_worldObjects, m_enemyPool, m_playerObject, *this);

		if (CheckAllEnemiesDead() == true) {
			for (size_t i = 0; i < 4; i++)
			{
				if (m_worldObjects[i]->GetIsActive() == true) {
					m_worldObjects[i]->CheckCollision(m_worldObjects, m_enemyPool, m_playerObject, *this);
				}
			}
		}

		for (std::shared_ptr<Object> b : m_bulletPool) {
			if (b->GetIsActive() == true) {
				b->CheckCollision(m_worldObjects, m_enemyPool, m_playerObject, *this);
			}
		}

		m_currentTime = HAPI.GetTime();

		if (m_currentTime - m_lastUpdateTime >= (DWORD)20) {
			m_lastUpdateTime = HAPI.GetTime();
			m_playerObject->Update(*this);
			for (std::shared_ptr<Object> o : m_bulletPool) {
				if (o->GetIsActive() == true) {
					o->Update(*this);
				}
			}

			for (std::shared_ptr<Object> o : m_worldObjects) {
				if (o->GetIsActive() == true) {
					o->Update(*this);
				}
			}

			for (std::shared_ptr<EnemyObject> e : m_enemyPool){
				if (e->GetIsActive() == true) {
					e->Update(*this);
				}
			}

			for (std::shared_ptr<Object> e : m_explosionPool) {
				if (e->GetIsActive() == true) {
					e->Update(*this);
				}
			}

			/*if (m_map->GetCurrentRoom().HasUpDoor() == true) {

			}
			else if (m_map->GetCurrentRoom().HasDownDoor() == true) {

			}
			else if (m_map->GetCurrentRoom().HasLeftDoor() == true) {

			}
			else if (m_map->GetCurrentRoom().HasRightDoor() == true) {

			}*/
		}

		DWORD timeElapsed = m_currentTime - m_lastUpdateTime;

		float fTime = (float)timeElapsed;
		fTime /= 50.0f;

		//std::cout << timeElapsed << std::endl;

		MasterRender(vis, fTime);
	}
}

void World::SpawnBullet(Vector3& p, Vector3& v, ObjectTag& t)
{
	for (std::shared_ptr<Object> b : m_bulletPool) {
		if (b->GetIsActive() == false && b->GetTag() == t) {
			b->SetPosition(p);
			b->SetVelocity(v);
			b->SetActive(true);
			m_audio->PlaySound("Shoot");
			break;
		}
	}
}

void World::SpawnExplosion(const Vector3& p)
{
	for (std::shared_ptr<Object> e : m_explosionPool) {
		if (e->GetIsActive() == false) {
			e->SetPosition(p);
			e->SetActive(true);
			m_audio->PlaySound("Explosion");
			break;
		}
	}
}

void World::MoveRoom(DoorDirection& d)
{
	if (CheckAllEnemiesDead() == false) {
		return;
	}
	std::cout << "Door Hit" << std::endl;
	Vector3 playerOffset = *m_playerObject->GetPosition();

	m_map->GetCurrentRoom().SetIsCleared(true);

	switch (d)
	{
	case DoorDirection::E_UP:
		m_map->StepRoom(RoomDirection::E_UP);
		playerOffset = *m_worldObjects[1]->GetPosition() + Vector3(0.0f, -96.0f, 0.0f);
		m_playerObject->SetPosition(playerOffset);
		break;
	case DoorDirection::E_DOWN:
		m_map->StepRoom(RoomDirection::E_DOWN);
		playerOffset = *m_worldObjects[0]->GetPosition() + Vector3(0.0f, 96.0f, 0.0f);
		m_playerObject->SetPosition(playerOffset);
		break;
	case DoorDirection::E_LEFT:
		m_map->StepRoom(RoomDirection::E_LEFT);
		playerOffset = *m_worldObjects[3]->GetPosition() + Vector3(-96.0f, 0.0f, 0.0f);
		m_playerObject->SetPosition(playerOffset);
		break;
	case DoorDirection::E_RIGHT:
		m_map->StepRoom(RoomDirection::E_RIGHT);
		playerOffset = *m_worldObjects[2]->GetPosition() + Vector3(96.0f, 0.0f, 0.0f);
		m_playerObject->SetPosition(playerOffset);
		break;
	default:
		break;
	}

	std::cout << "X: " << m_playerObject->GetPosition()->GetX() << " Y: " << m_playerObject->GetPosition()->GetY() << std::endl;

	if (m_map->GetCurrentRoom().HasUpDoor() == true) {
		m_worldObjects[0]->SetActive(true);
	}
	else {
		m_worldObjects[0]->SetActive(false);
	}

	if (m_map->GetCurrentRoom().HasDownDoor() == true) {
		m_worldObjects[1]->SetActive(true);
	}
	else {
		m_worldObjects[1]->SetActive(false);
	}

	if (m_map->GetCurrentRoom().HasLeftDoor() == true) {
		m_worldObjects[2]->SetActive(true);
	}
	else {
		m_worldObjects[2]->SetActive(false);
	}

	if (m_map->GetCurrentRoom().HasRightDoor() == true) {
		m_worldObjects[3]->SetActive(true);
	}
	else {
		m_worldObjects[3]->SetActive(false);
	}

	if (m_map->GetCurrentRoom().GetIsCleared() == false) {
		SpawnEnemies();
	}
}

const Vector3& World::GetEnemyPosition(size_t i)
{
	if (i > m_worldObjects.size()) {
		HAPI.UserMessage("Tried to fetch AI position out of range", "ERROR");
		HAPI.Close();
	}
	return *m_worldObjects[i + 4]->GetPosition();
}

void World::SetAIVelocity(size_t i, Vector3& v)
{
	if (i > m_worldObjects.size()) {
		HAPI.UserMessage("Tried to fetch AI position out of range", "ERROR");
		HAPI.Close();
	}

	m_worldObjects[i + 4]->SetVelocity(v);
}

const Vector3& World::GetPlayerPosition()
{
	return *m_playerObject->GetPosition();
}

void World::MasterRender(Visualisation& v, float s)
{
	//Updates animation if set time has elapsed
	if (m_currentTime - m_lastAnimationTime >= (DWORD)33) {
		//Update animations here
		m_playerObject->SetCurrentFrame(m_playerObject->GetCurrentFrame() + 1);
		for (std::shared_ptr<Object> o : m_worldObjects) {
			o->SetCurrentFrame(o->GetCurrentFrame() + 1);
		}

		for (std::shared_ptr<Object> e : m_explosionPool) {
			e->SetCurrentFrame(e->GetCurrentFrame() + 1);
		}

		m_lastAnimationTime = HAPI.GetTime();
		//std::cout << "Yes Animation" << std::endl;
	}

	/*float fs = (float)s;

	Vector3 lerpPosition;
	lerpPosition.Lerp(*m_playerObject->GetPosition(), *m_playerObject->GetPosition() + *m_playerObject->GetVelocity(), fs / (DWORD)20);

	std::cout << "X: " << lerpPosition.GetX() << " Y: " << lerpPosition.GetY() << std::endl;
	std::cout << (float)(s / (DWORD)100) << std::endl;

	const Vector3 lerped = lerpPosition;*/

	//Renders each object, taking in the key for the texture
	//Ends the program if an invalid key is passed in
	//Will return false if this is the case
	m_playerObject->Render(v, s);

	for (std::shared_ptr<Object> o : m_worldObjects) {
		o->Render(v, s);
	}

	for (std::shared_ptr<Object> o : m_bulletPool) {
		o->Render(v, s);
	}

	for (std::shared_ptr<EnemyObject> o : m_enemyPool) {
		o->Render(v, s);
	}

	for (std::shared_ptr<Object> e : m_explosionPool) {
		e->Render(v, s);
	}
}

bool World::CheckAllEnemiesDead()
{
	bool allDead{ true };

	for (std::shared_ptr<EnemyObject> o : m_enemyPool) {
		if (o->GetIsActive() == true) {
			allDead = false;
			break;
		}
	}

	return allDead;
}

void World::SpawnEnemies()
{
	std::vector<Vector3> points = m_map->GetCurrentRoom().GetSpawnPoints();

	int numberToSpawn = std::rand() % points.size();

	for (size_t i = 0; i <= numberToSpawn; i++)
	{
		int rng = std::rand() % m_enemyPool.size();

		if (m_enemyPool[rng]->GetIsActive() == true) {
			i--;
		}
		else {
			m_enemyPool[rng]->SetActive(true);
			m_enemyPool[rng]->SetPosition(points[i]);
		}
	}
}
