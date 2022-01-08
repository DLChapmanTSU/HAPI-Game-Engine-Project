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
#include "BossEnemyObject.h"
#include "ExplosionObject.h"
#include "Audio.h"
#include "StatBar.h"
#include "Button.h"

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
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 200.0f, 600.0f, 0.0f, 4));*/
	//m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 300.0f, 100.0f, 0.0f, 4));

	for (size_t i = 0; i < 200; i++)
	{
		m_bulletPool.push_back(std::make_shared<BulletObject>(std::pair<int, int>(32, 32), "Bullet", 0.0f, 0.0f, 0.0f, 0, ObjectTag::E_FRIENDLY_BULLET, false));
		m_bulletPool.push_back(std::make_shared<BulletObject>(std::pair<int, int>(32, 32), "Bullet", 0.0f, 0.0f, 0.0f, 0, ObjectTag::E_ENEMY_BULLET, false));
	}

	for (size_t i = 0; i < 20; i++)
	{
		m_explosionPool.push_back(std::make_shared<ExplosionObject>(std::pair<int, int>(64, 64), "Test", 300.0f, 100.0f, 0.0f, 4, ObjectTag::E_PARTICLE, false));
	}

	m_currentTime = HAPI.GetTime();
	m_lastUpdateTime = HAPI.GetTime();
	m_lastAnimationTime = HAPI.GetTime();

	Map myMap;
	//myMap.GenerateMap();
	//std::cout << "Generation Attempted" << std::endl;

	m_map = std::make_shared<Map>(myMap);
	//m_map->GenerateMap();

	m_roamingEnemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_chasingEnemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_roamingEnemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_chasingEnemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_roamingEnemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_chasingEnemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_roamingEnemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_chasingEnemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_roamingEnemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_chasingEnemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	/*m_enemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<RoamingEnemyObject>(std::pair<int, int>(64, 64), "RoamingEnemy", 480.0f, 100.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	m_enemyPool.push_back(std::make_shared<ChasingEnemyObject>(std::pair<int, int>(64, 64), "ChasingEnemy", 800.0f, 300.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));*/
	m_bossEnemy = std::make_shared<BossEnemyObject>(std::pair<int, int>(80, 80), "BossEnemy", 300.0f, 100.0f, 0.0f, 16, ObjectTag::E_ENEMY, false);
	m_audio = std::make_shared<Audio>(Audio());

	m_playerHealthBar = std::make_shared<StatBar>(Vector3(10.0f, 738.0f, 0.0f), m_playerObject->GetHealth(), HAPI_TColour::RED);
	m_resumeButton = std::make_shared<Button>(Vector3(100.0f, 100.0f, 0.0f), 150, 100, "Resume");
	m_restartButton = std::make_shared<Button>(Vector3(100.0f, 300.0f, 0.0f), 150, 100, "Restart");
	m_quitButton = std::make_shared<Button>(Vector3(100.0f, 500.0f, 0.0f), 150, 100, "Quit");

	m_worldStartSize = m_worldObjects.size();
}

void World::Run()
{
	std::srand((unsigned int)time(NULL));
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
	vis.GenerateSprite("Data\\BossEnemy.png", "BossEnemy", 80, 80, true, 1280, 80, true);
	vis.GenerateSprite("Data\\RocketTarget.png", "Target", 64, 64, true, 64, 64, false);

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

		

		

		if (m_playerObject->GetHealth() <= 0) {
			HAPI.RenderText(200, 384, HAPI_TColour::BLACK, HAPI_TColour::WHITE, 2.0f, "Game Over", 100);
			m_restartButton->SetIsActive(true);
			m_quitButton->SetIsActive(true);

			HAPI_TMouseData mouseData = HAPI.GetMouseData();

			if (mouseData.leftButtonDown == true) {
				Vector3 mousePos;
				mousePos.SetX((float)mouseData.x);
				mousePos.SetY((float)mouseData.y);
				bool isRestartClicked = m_restartButton->HasClick(mousePos);
				bool isQuitClicked = m_quitButton->HasClick(mousePos);
				if (isRestartClicked == true) {
					std::cout << "Button Pressed" << std::endl;
					ResetWorld();
				}
				else if (isQuitClicked == true) {
					HAPI.Close();
				}
			}
		}
		else if (CheckAllEnemiesDead() == true && m_map->GetCurrentRoom().GetIsBossRoom() == true) {
			HAPI.RenderText(200, 384, HAPI_TColour::BLACK, HAPI_TColour::WHITE, 2.0f, "You Win", 100);

			m_restartButton->SetIsActive(true);
			m_quitButton->SetIsActive(true);

			HAPI_TMouseData mouseData = HAPI.GetMouseData();

			if (mouseData.leftButtonDown == true) {
				Vector3 mousePos;
				mousePos.SetX((float)mouseData.x);
				mousePos.SetY((float)mouseData.y);
				bool isRestartClicked = m_restartButton->HasClick(mousePos);
				bool isQuitClicked = m_quitButton->HasClick(mousePos);
				if (isRestartClicked == true) {
					std::cout << "Button Pressed" << std::endl;
					ResetWorld();
				}
				else if (isQuitClicked == true) {
					HAPI.Close();
				}
			}
		}
		else if (m_isPaused == true) {
			HAPI.RenderText(200, 384, HAPI_TColour::BLACK, HAPI_TColour::WHITE, 2.0f, "Paused", 100);
			m_restartButton->SetIsActive(true);
			m_quitButton->SetIsActive(true);
			m_resumeButton->SetIsActive(true);

			HAPI_TMouseData mouseData = HAPI.GetMouseData();

			if (mouseData.leftButtonDown == true) {
				Vector3 mousePos;
				mousePos.SetX((float)mouseData.x);
				mousePos.SetY((float)mouseData.y);
				bool isRestartClicked = m_restartButton->HasClick(mousePos);
				bool isQuitClicked = m_quitButton->HasClick(mousePos);
				bool isResumeClicked = m_resumeButton->HasClick(mousePos);
				if (isRestartClicked == true) {
					std::cout << "Button Pressed" << std::endl;
					ResetWorld();
				}
				else if (isQuitClicked == true) {
					HAPI.Close();
				}
				else if (isResumeClicked == true) {
					m_restartButton->SetIsActive(false);
					m_quitButton->SetIsActive(false);
					m_resumeButton->SetIsActive(false);
					m_isPaused = false;
				}
			}
		}
		else {

			HAPI_TKeyboardData keyboardData = HAPI.GetKeyboardData();
			HAPI_TControllerData controllerData = HAPI.GetControllerData(0);

			if (controllerData.isAttached == true) {
				if (controllerData.digitalButtons[HK_DIGITAL_START] == true) {
					m_isPaused = true;
				}
			}
			else {
				if (keyboardData.scanCode[HK_ESCAPE] == true) {
					std::cout << "Paused" << std::endl;
					m_isPaused = true;
				}
			}

			m_playerObject->CheckCollision(m_worldObjects, m_playerObject, *this);

			if (CheckAllEnemiesDead() == true) {
				for (size_t i = 0; i < 4; i++)
				{
					if (m_worldObjects[i]->GetIsActive() == true) {
						m_worldObjects[i]->CheckCollision(m_worldObjects, m_playerObject, *this);
					}
				}
			}

			for (size_t i = 0; i < m_worldObjects.size(); i++)
			{
				if (m_worldObjects[i]->GetIsActive() == true) {
					m_worldObjects[i]->CheckCollision(m_worldObjects, m_playerObject, *this);
				}
			}

			m_currentTime = HAPI.GetTime();

			if (m_currentTime - m_lastUpdateTime >= (DWORD)20) {
				CleaUpRuntimeObjects();
				m_lastUpdateTime = HAPI.GetTime();
				m_playerObject->Update(*this);

				for (size_t i = 0; i < m_worldObjects.size(); i++)
				{
					if (m_worldObjects[i]->GetIsActive() == true) {
						m_worldObjects[i]->Update(*this);
					}
				}

				m_playerHealthBar->SetValue(m_playerObject->GetHealth());
			}
		}

		

		//Check collisions between each object
		

		DWORD timeElapsed = m_currentTime - m_lastUpdateTime;

		float fTime = (float)timeElapsed;
		fTime /= 50.0f;

		//std::cout << timeElapsed << std::endl;

		MasterRender(vis, fTime);
	}
}

void World::SpawnBullet(Vector3& p, Vector3& v, ObjectTag t)
{
	for (size_t i = 0; i < m_bulletPool.size(); i++)
	{
		if (m_bulletPool[i]->GetIsActive() == false && m_bulletPool[i]->GetTag() == t) {
			m_bulletPool[i]->SetPosition(p);
			m_bulletPool[i]->SetVelocity(v);
			m_bulletPool[i]->SetActive(true);
			m_bulletPool[i]->ResetTimer();
			//std::make_shared<BulletObject>(*m_bulletPool[i]);
			//BulletObject& b = *m_bulletPool[i];
			m_worldObjects.push_back(m_bulletPool[i]);
			m_audio->PlaySound("Shoot");
			m_otherExtraInstanceCount++;
			break;
		}
	}
}

void World::SpawnExplosion(const Vector3& p)
{
	for (size_t i = 0; i < m_explosionPool.size(); i++) {
		if (m_explosionPool[i]->GetIsActive() == false) {
			m_explosionPool[i]->SetPosition(p);
			m_explosionPool[i]->SetActive(true);
			m_worldObjects.push_back(m_explosionPool[i]);
			m_audio->PlaySound("Explosion");
			m_otherExtraInstanceCount++;
			break;
		}
	}
}

void World::MoveRoom(DoorDirection& d)
{
	if (CheckAllEnemiesDead() == false) {
		return;
	}

	for (int i = 0; i < m_enemyCount + m_otherExtraInstanceCount; i++)
	{
		if (m_worldObjects.size() <= m_worldStartSize) {
			break;
		}
		else {
			m_worldObjects.pop_back();
		}
	}

	std::cout << "Door Hit" << std::endl;
	Vector3 playerOffset = *m_playerObject->GetPosition();

	m_map->GetCurrentRoom().SetIsCleared(true);

	m_otherExtraInstanceCount = 0;

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
	else {
		m_enemyCount = 0;
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

		/*for (std::shared_ptr<Object> e : m_explosionPool) {
			e->SetCurrentFrame(e->GetCurrentFrame() + 1);
		}

		for (std::shared_ptr<EnemyObject> e : m_enemyPool) {
			e->SetCurrentFrame(e->GetCurrentFrame() + 1);
		}*/

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

	for (size_t i = 0; i < m_worldObjects.size(); i++)
	{
		m_worldObjects[i]->Render(v, s);
	}

	/*for (std::shared_ptr<Object> o : m_worldObjects) {
		o->Render(v, s);
	}*/

	/*for (std::shared_ptr<Object> o : m_bulletPool) {
		o->Render(v, s);
	}*/

	/*for (std::shared_ptr<EnemyObject> o : m_enemyPool) {
		o->Render(v, s);
	}*/

	/*for (std::shared_ptr<Object> e : m_explosionPool) {
		e->Render(v, s);
	}*/

	m_playerHealthBar->Render(v);

	m_resumeButton->Render(v);
	m_restartButton->Render(v);
	m_quitButton->Render(v);
	//v.RenderDefault(Vector3(10.0f, 10.0f, 0.0f), 100, 20, HAPI_TColour::GREEN);
}

bool World::CheckAllEnemiesDead()
{
	if (m_enemyCount <= 0) {
		return true;
	}

	bool allDead{ true };

	int startPoint = (int)m_worldObjects.size() - m_enemyCount - m_otherExtraInstanceCount;

	if (startPoint <= 3) {
		return true;
	}

	int endPoint = (int)m_worldObjects.size() - m_otherExtraInstanceCount;

	for (int i = startPoint; i < endPoint; i++)
	{
		if (m_worldObjects[i]->GetIsActive() == true) {
			allDead = false;
			break;
		}
	}

	/*for (std::shared_ptr<EnemyObject> o : m_enemyPool) {
		if (o->GetIsActive() == true) {
			allDead = false;
			break;
		}
	}*/

	return allDead;
}

void World::SpawnEnemies()
{
	std::vector<Vector3> points = m_map->GetCurrentRoom().GetSpawnPoints();

	if (m_map->GetCurrentRoom().GetIsBossRoom() == true) {
		/*m_enemyPool[m_enemyPool.size() - 1]->SetActive(true);
		m_enemyPool[m_enemyPool.size() - 1]->SetPosition(Vector3(472.0f, 344.0f, 0.0f));
		m_enemyPool[m_enemyPool.size() - 1]->Reset();*/
		m_enemyCount = 1;
		m_bossEnemy->SetActive(true);
		m_bossEnemy->SetPosition(Vector3(472.0f, 344.0f, 0.0f));
		m_bossEnemy->Reset();
		m_worldObjects.push_back(m_bossEnemy);
		return;
	}

	int numberToSpawn = std::rand() % points.size();

	m_enemyCount = numberToSpawn + 1;

	for (size_t i = 0; i <= numberToSpawn; i++)
	{
		int rng = std::rand() % 2;

		switch (rng)
		{
		case 0:
			for (size_t j = 0; j < 5; j++)
			{
				if (m_roamingEnemyPool[j]->GetIsActive() == false) {
					m_roamingEnemyPool[j]->Reset();
					m_roamingEnemyPool[j]->SetActive(true);
					m_roamingEnemyPool[j]->SetPosition(points[i]);

					m_worldObjects.push_back(m_roamingEnemyPool[j]);
					break;
				}
			}
			break;
		case 1:
			for (size_t j = 0; j < 5; j++)
			{
				if (m_chasingEnemyPool[j]->GetIsActive() == false) {
					m_chasingEnemyPool[j]->Reset();
					m_chasingEnemyPool[j]->SetActive(true);
					m_chasingEnemyPool[j]->SetPosition(points[i]);

					m_worldObjects.push_back(m_chasingEnemyPool[j]);
					break;
				}
			}
			break;
		default:
			break;
		}

		/*if (m_enemyPool[rng]->GetIsActive() == true) {
			i--;
		}
		else {
			m_enemyPool[rng]->SetActive(true);
			m_enemyPool[rng]->SetPosition(points[i]);
			m_enemyPool[rng]->Reset();

			std::shared_ptr<Object> obj = std::make_shared<Object>(*m_enemyPool[rng]);
			m_worldObjects.push_back(obj);
		}*/
	}
}

void World::ResetWorld()
{
	m_isPaused = false;

	while (m_worldObjects.size() > m_worldStartSize) {
		m_worldObjects.pop_back();
	}

	for (std::shared_ptr<Object> b : m_bulletPool) {
		b->SetActive(false);
	}

	for (std::shared_ptr<Object> e : m_explosionPool) {
		e->SetActive(false);
	}

	for (std::shared_ptr<RoamingEnemyObject> e : m_roamingEnemyPool) {
		e->Reset();
	}

	for (std::shared_ptr<ChasingEnemyObject> e : m_chasingEnemyPool) {
		e->Reset();
	}

	m_bossEnemy->Reset();

	for (std::shared_ptr<Object> o : m_worldObjects) {
		if (o->GetTag() == ObjectTag::E_DOOR) {
			o->SetActive(true);
		}
		else {
			o->SetActive(false);
		}
	}

	m_playerObject->SetActive(true);
	m_playerObject->SetPosition(Vector3(301.0f, 301.0f, 0.0f));
	m_playerObject->Reset();

	m_map->GenerateMap();
	m_enemyCount = 0;
	m_otherExtraInstanceCount = 0;
	m_restartButton->SetIsActive(false);
	m_resumeButton->SetIsActive(false);
	m_quitButton->SetIsActive(false);
	SpawnEnemies();
}

void World::CleaUpRuntimeObjects()
{
	int loopStart = (int)m_worldObjects.size() - m_otherExtraInstanceCount;

	for (size_t i = loopStart; i < m_worldObjects.size(); i++)
	{
		if (m_worldObjects[i]->GetIsActive() == false && m_worldObjects[i]->GetTag() != ObjectTag::E_DOOR) {
			/*std::shared_ptr<EnemyObject> temp = std::dynamic_pointer_cast<EnemyObject>(m_worldObjects[i]);
			if (temp == nullptr) {
				std::cout << "Isn't an enemy" << std::endl;
				m_otherExtraInstanceCount--;
			}
			else {
				m_enemyCount--;
			}*/
			m_worldObjects.erase(m_worldObjects.begin() + i);
			m_otherExtraInstanceCount--;
			i--;
		}
	}
}