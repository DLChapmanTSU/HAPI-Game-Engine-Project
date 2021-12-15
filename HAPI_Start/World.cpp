#include "World.h"
#include "Object.h"
#include "Vector3.h"
#include "Visualisation.h"
#include "CharacterObject.h"
#include "PlayerObject.h"
#include "BulletObject.h"
#include "WallObject.h"
#include "Map.h"
#include "Room.h"

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>

#include <memory>
#include <random>

World::World()
{
	//Create Player
	m_playerObject = std::make_shared<PlayerObject>(std::pair<int, int>(64, 64), "Player", 301.0f, 301.0f, 0.0f, 0, ObjectTag::E_FRIENDLY, true);
	//Create world objects for game
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(256, 256), "Background", 100.0f, 100.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 200.0f, 100.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 200.0f, 500.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 290.0f, 180.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 750.0f, 100.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 0.0f, 0.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 300.0f, 300.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 200.0f, 600.0f, 0.0f, 4));
	m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Test", 300.0f, 100.0f, 0.0f, 4));

	for (size_t i = 0; i < 100; i++)
	{
		m_bulletPool.push_back(std::make_shared<BulletObject>(std::pair<int, int>(32, 32), "Bullet", 0.0f, 0.0f, 0.0f, 0, ObjectTag::E_FRIENDLY, false));
		m_bulletPool.push_back(std::make_shared<BulletObject>(std::pair<int, int>(32, 32), "Bullet", 0.0f, 0.0f, 0.0f, 0, ObjectTag::E_ENEMY, false));
	}

	m_currentTime = HAPI.GetTime();
	m_lastUpdateTime = HAPI.GetTime();
	m_lastAnimationTime = HAPI.GetTime();

	Map myMap;
	//myMap.GenerateMap();
	//std::cout << "Generation Attempted" << std::endl;

	m_map = std::make_shared<Map>(myMap);
	//m_map->GenerateMap();
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

	HAPI.SetShowFPS(true);
	HAPI.LimitFrameRate(60);



	while (HAPI.Update()) {
		//Clears screen to given colour
		HAPI_TColour bgColour(10, 56, 33, 255);
		vis.ClearToColour(bgColour, 1024, 768);

		

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
		m_playerObject->CheckCollision(m_worldObjects, m_playerObject);

		m_currentTime = HAPI.GetTime();

		if (m_currentTime - m_lastUpdateTime >= (DWORD)20) {
			m_lastUpdateTime = HAPI.GetTime();
			m_playerObject->Update(*this);
			for (std::shared_ptr<Object> o : m_bulletPool) {
				if (o->GetIsActive() == true) {
					o->Update(*this);
				}
			}
		}

		DWORD timeElapsed = m_currentTime - m_lastUpdateTime;

		float fTime = (float)timeElapsed;
		fTime /= 50.0f;

		//std::cout << timeElapsed << std::endl;

		MasterRender(vis, fTime);
	}
}

void World::SpawnBullet(Vector3& p, Vector3& v)
{
	for (std::shared_ptr<Object> b : m_bulletPool) {
		if (b->GetIsActive() == false) {
			b->SetPosition(p);
			b->SetVelocity(v);
			b->SetActive(true);
			break;
		}
	}
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
}
