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
#include <iostream>
#include <fstream>
#include <ctime>

World::World()
{
	//Create Player
	m_playerObject = std::make_shared<PlayerObject>(std::pair<int, int>(32, 64), "Player", 301.0f, 301.0f, 0.0f, 2, ObjectTag::E_FRIENDLY, true);
	//Create Doors
	m_worldObjects.push_back(std::make_shared<DoorObject>(DoorDirection::E_UP, std::pair<int, int>(64, 64), "Door", 480.0f, 64.0f, 0.0f, 0, ObjectTag::E_DOOR, true));
	m_worldObjects.push_back(std::make_shared<DoorObject>(DoorDirection::E_DOWN, std::pair<int, int>(64, 64), "Door", 480.0f, 640.0f, 0.0f, 0, ObjectTag::E_DOOR, true));
	m_worldObjects.push_back(std::make_shared<DoorObject>(DoorDirection::E_LEFT, std::pair<int, int>(64, 64), "Door", 64.0f, 384.0f, 0.0f, 0, ObjectTag::E_DOOR, true));
	m_worldObjects.push_back(std::make_shared<DoorObject>(DoorDirection::E_RIGHT, std::pair<int, int>(64, 64), "Door", 896.0f, 384.0f, 0.0f, 0, ObjectTag::E_DOOR, true));
	//Create world objects for game
	for (size_t i = 0; i < 16; i++)
	{
		m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Wall", 64.0f * i, 0.0f, 0.0f, 0, ObjectTag::E_NEUTRAL, true));
		m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Wall", 64.0f * i, 704.0f, 0.0f, 0, ObjectTag::E_NEUTRAL, true));
	}

	for (size_t i = 1; i < 11; i++)
	{
		m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Wall", 0.0f, 64.0f * i, 0.0f, 0, ObjectTag::E_NEUTRAL, true));
		m_worldObjects.push_back(std::make_shared<WallObject>(std::pair<int, int>(64, 64), "Wall", 960.0f, 64.0f * i, 0.0f, 0, ObjectTag::E_NEUTRAL, true));
	}

	//Fills object pools
	for (size_t i = 0; i < 200; i++)
	{
		m_bulletPool.push_back(std::make_shared<BulletObject>(std::pair<int, int>(32, 32), "Bullet", 0.0f, 0.0f, 0.0f, 0, ObjectTag::E_FRIENDLY_BULLET, false));
		m_bulletPool.push_back(std::make_shared<BulletObject>(std::pair<int, int>(32, 32), "Bullet", 0.0f, 0.0f, 0.0f, 0, ObjectTag::E_ENEMY_BULLET, false));
	}

	for (size_t i = 0; i < 20; i++)
	{
		m_explosionPool.push_back(std::make_shared<ExplosionObject>(std::pair<int, int>(96, 96), "Explosion", 300.0f, 100.0f, 0.0f, 4, ObjectTag::E_PARTICLE, false));
	}

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
	m_resumeButton = std::make_shared<Button>(Vector3(437.0f, 100.0f, 0.0f), 150, 100, "Resume");
	m_restartButton = std::make_shared<Button>(Vector3(437.0f, 300.0f, 0.0f), 150, 100, "Restart");
	m_quitButton = std::make_shared<Button>(Vector3(437.0f, 500.0f, 0.0f), 150, 100, "Quit");
	m_easyButton = std::make_shared<Button>(Vector3(437.0f, 100.0f, 0.0f), 150, 100, "Easy");
	m_normalButton = std::make_shared<Button>(Vector3(437.0f, 300.0f, 0.0f), 150, 100, "Normal");
	m_hardButton = std::make_shared<Button>(Vector3(437.0f, 500.0f, 0.0f), 150, 100, "Hard");

	m_worldStartSize = m_worldObjects.size();

	std::ifstream reader("Data\\saveData.txt");

	if (!reader.is_open()) {
		HAPI.UserMessage("Could not open file for save data", "ERROR");
		HAPI.Close();
		return;
	}

	reader >> m_highscore;

	reader.close();

	m_cameraPosition = Vector3(0.0f, 0.0f, 0.0f);
	m_lastUpdate = std::chrono::steady_clock::now();
	m_lastAnimation = std::chrono::steady_clock::now();
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

	//Load in all needed sprites
	Visualisation vis(width, height);
	vis.GenerateSprite("Data\\Player.png", "Player", 32, 64, true, 64, 64, true);
	vis.GenerateSprite("Data\\shapeTest.png", "Test", 64, 64, true, 256, 64, true);
	vis.GenerateSprite("Data\\background.tga", "Background", 256, 256, false, 256, 256, false);
	vis.GenerateSprite("Data\\Bullet.png", "Bullet", 32, 32, true, 32, 32, false);
	vis.GenerateSprite("Data\\Door.png", "Door", 64, 64, true, 64, 64, false);
	vis.GenerateSprite("Data\\RoamingEnemy.png", "RoamingEnemy", 64, 64, true, 64, 64, false);
	vis.GenerateSprite("Data\\ChasingEnemy.png", "ChasingEnemy", 64, 64, true, 64, 64, false);
	vis.GenerateSprite("Data\\BossEnemy.png", "BossEnemy", 80, 80, true, 1280, 80, true);
	vis.GenerateSprite("Data\\RocketTarget.png", "Target", 64, 64, true, 64, 64, false);
	vis.GenerateSprite("Data\\Explosion.png", "Explosion", 96, 96, true, 384, 96, true);
	vis.GenerateSprite("Data\\Wall.png", "Wall", 64, 64, false, 64, 64, false);

	//Audio aud;
	//m_audio = aud;
	m_audio->LoadSound("Data\\Audio\\shoot.wav", "Shoot", false, 0.0f, 1.0f, 0.1f);
	m_audio->LoadSound("Data\\Audio\\explosion.wav", "Explosion", false, 0.0f, 1.0f, 1.0f);

	HAPI.SetShowFPS(true);
	HAPI.LimitFrameRate(60);

	

	//Main loop
	while (HAPI.Update()) {
		//Clears screen to given colour
		HAPI_TColour bgColour(10, 56, 33, 255);
		vis.ClearToColour(m_map->GetCurrentRoom().GetColour(), 1024, 768);

		if (m_isPlaying == false) {
			m_easyButton->SetIsActive(true);
			m_normalButton->SetIsActive(true);
			m_hardButton->SetIsActive(true);

			HAPI.RenderText(10, 738, HAPI_TColour::BLACK, "Highscore: " + std::to_string(m_highscore), 20);

			HAPI_TMouseData mouseData = HAPI.GetMouseData();

			//Will check to see if the mouse cursor is over a button when left click is pressed
			//Will either reset the game or close the game depending on the button pressed
			if (mouseData.leftButtonDown == true) {
				Vector3 mousePos;
				mousePos.SetX((float)mouseData.x);
				mousePos.SetY((float)mouseData.y);

				bool isEasyClicked = m_easyButton->HasClick(mousePos);
				bool isNormalClicked = m_normalButton->HasClick(mousePos);
				bool isHardClicked = m_hardButton->HasClick(mousePos);

				if (isEasyClicked == true) {
					m_difficulty = Difficulty::E_EASY;
					m_easyButton->SetIsActive(false);
					m_normalButton->SetIsActive(false);
					m_hardButton->SetIsActive(false);
					m_isPlaying = true;
					SpawnEnemies();
				}
				else if (isNormalClicked == true) {
					m_difficulty = Difficulty::E_NORMAL;
					m_easyButton->SetIsActive(false);
					m_normalButton->SetIsActive(false);
					m_hardButton->SetIsActive(false);
					m_isPlaying = true;
					SpawnEnemies();
				}
				else if (isHardClicked == true) {
					m_difficulty = Difficulty::E_HARD;
					m_easyButton->SetIsActive(false);
					m_normalButton->SetIsActive(false);
					m_hardButton->SetIsActive(false);
					m_isPlaying = true;
					SpawnEnemies();
				}
			}

			MasterRender(vis, 0.0f);
			continue;
		}
		else {
			//Checks to see if the game is over or the game is paused
			//Renders the corresponding buttons if so
			//If not, the game updates as normal
			if (m_playerObject->GetHealth() <= 0) {
				SavePoints();
				HAPI.RenderText(200, 384, HAPI_TColour::BLACK, HAPI_TColour::WHITE, 2.0f, "Game Over", 100);
				m_restartButton->SetIsActive(true);
				m_quitButton->SetIsActive(true);

				HAPI_TMouseData mouseData = HAPI.GetMouseData();

				//Will check to see if the mouse cursor is over a button when left click is pressed
				//Will either reset the game or close the game depending on the button pressed
				if (mouseData.leftButtonDown == true) {
					Vector3 mousePos;
					mousePos.SetX((float)mouseData.x);
					mousePos.SetY((float)mouseData.y);
					bool isRestartClicked = m_restartButton->HasClick(mousePos);
					bool isQuitClicked = m_quitButton->HasClick(mousePos);
					if (isRestartClicked == true) {
						std::cout << "Button Pressed" << std::endl;
						m_points = 0;
						ResetWorld();
					}
					else if (isQuitClicked == true) {
						HAPI.Close();
					}
				}
			}
			else if (CheckAllEnemiesDead() == true && m_map->GetCurrentRoom().GetIsBossRoom() == true && m_bossEnemy->GetIsActive() == false) {
				GainPoints(500);
				HAPI.RenderText(200, 384, HAPI_TColour::BLACK, HAPI_TColour::WHITE, 2.0f, "You Win", 100);

				m_restartButton->SetIsActive(true);
				m_quitButton->SetIsActive(true);

				HAPI_TMouseData mouseData = HAPI.GetMouseData();

				//Will check to see if the mouse cursor is over a button when left click is pressed
				//Will either reset the game or close the game depending on the button pressed
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
						SavePoints();
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

				//Will check to see if the mouse cursor is over a button when left click is pressed
				//Will either reset the game, resume the game or close the game depending on the button pressed
				if (mouseData.leftButtonDown == true) {
					Vector3 mousePos;
					mousePos.SetX((float)mouseData.x);
					mousePos.SetY((float)mouseData.y);
					bool isRestartClicked = m_restartButton->HasClick(mousePos);
					bool isQuitClicked = m_quitButton->HasClick(mousePos);
					bool isResumeClicked = m_resumeButton->HasClick(mousePos);
					if (isRestartClicked == true) {
						std::cout << "Button Pressed" << std::endl;
						SavePoints();
						m_points = 0;
						ResetWorld();
					}
					else if (isQuitClicked == true) {
						SavePoints();
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
				//Main update loop
				HAPI_TKeyboardData keyboardData = HAPI.GetKeyboardData();
				HAPI_TControllerData controllerData = HAPI.GetControllerData(0);

				//Pauses the game if escape/the start button is pressed
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

				//Checks collisions for all world objects
				for (size_t i = 0; i < m_worldObjects.size(); i++)
				{
					if (m_worldObjects[i]->GetIsActive() == true) {
						m_worldObjects[i]->CheckCollision(m_worldObjects, m_playerObject, *this);
					}
				}


				//Will only run object update functions after a set period of time
				//This is to keep consistency between computers running the game at lower framerates
				std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
				float timePassed = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(time - m_lastUpdate).count();
				//std::cout << timePassed << std::endl;

				if (timePassed >= 20000000.0f) {
					std::cout << "Tick" << std::endl;
					CleaUpRuntimeObjects();
					m_lastUpdate = std::chrono::steady_clock::now();
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

			//Renders each object once per frame
			//Calculates the time between updates so that we can lerp between where each object was in the last update and where it will be next update
			std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
			
			float timeElapsed = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(time - m_lastUpdate).count();

			float fTime = timeElapsed / 20000000.0f;
			
			//fTime /= 50.0f;

			//float playerSpeed = *m_playerObject->GetMoveSpeed();
			m_cameraPosition = *m_playerObject->GetPosition() - Vector3((float)width / 2, (float)height / 2, 0.0f);
			m_cameraPosition.Lerp(m_cameraPosition, m_cameraPosition + (*m_playerObject->GetVelocity() * m_playerObject->GetMoveSpeed()), fTime);

			MasterRender(vis, fTime);
		}
	}

		
}

//Loops through the bullet pool to spawn a bullet at a set position and velocity with a set tag
void World::SpawnBullet(Vector3& p, Vector3& v, ObjectTag t)
{
	for (size_t i = 0; i < m_bulletPool.size(); i++)
	{
		if (m_bulletPool[i]->GetIsActive() == false && m_bulletPool[i]->GetTag() == t) {
			m_bulletPool[i]->SetPosition(p);
			m_bulletPool[i]->SetVelocity(v);
			m_bulletPool[i]->SetActive(true);
			m_bulletPool[i]->ResetTimer();
			m_worldObjects.push_back(m_bulletPool[i]);
			m_audio->PlaySound("Shoot");
			m_otherExtraInstanceCount++;
			break;
		}
	}
}

//Loops through the explosion pool to find an inactive explosion
//Spawns it in at a set position
void World::SpawnExplosion(const Vector3& p)
{
	for (size_t i = 0; i < m_explosionPool.size(); i++) {
		if (m_explosionPool[i]->GetIsActive() == false) {
			m_explosionPool[i]->SetPosition(p);
			m_explosionPool[i]->SetActive(true);
			m_explosionPool[i]->SetCurrentFrame(0);
			m_worldObjects.push_back(m_explosionPool[i]);
			m_audio->PlaySound("Explosion");
			m_otherExtraInstanceCount++;
			break;
		}
	}
}

//Moves to the next room if all enemies are dead
void World::MoveRoom(DoorDirection& d)
{
	if (CheckAllEnemiesDead() == false) {
		return;
	}

	//Clears all non-permanent objects from the world vector
	//The only permanent objects are the edge walls and the doors
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

	//Based on the door entered, the game steps the current room to the next room
	//Player is then placed to the opposite side of the room to the door they walked into
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

	//Sets each door to active based on which doors are in the new room
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

	//Spawns in enemies if the player hasn't entered the new room yet
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

const Vector3& World::GetPlayerPosition()
{
	return *m_playerObject->GetPosition();
}

void World::GainPoints(const size_t p)
{
	size_t multiplier{ 1 };

	switch (m_difficulty)
	{
	case Difficulty::E_EASY:
		multiplier = 1;
		break;
	case Difficulty::E_NORMAL:
		multiplier = 2;
		break;
	case Difficulty::E_HARD:
		multiplier = 3;
		break;
	default:
		break;
	}

	m_points = m_points + (p * multiplier);
}

void World::MasterRender(Visualisation& v, float s)
{
	if (m_isPlaying == false) {
		m_easyButton->Render(v);
		m_normalButton->Render(v);
		m_hardButton->Render(v);
		return;
	}

	std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
	float timePassed = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(time - m_lastAnimation).count();
	//Updates animation if set time has elapsed
	if (timePassed >= 33333333.33f) {
		//Update animations here
		m_playerObject->SetCurrentFrame(m_playerObject->GetCurrentFrame() + 1);
		for (std::shared_ptr<Object> o : m_worldObjects) {
			o->SetCurrentFrame(o->GetCurrentFrame() + 1);
		}
		std::chrono::steady_clock::time_point m_lastAnimation = std::chrono::steady_clock::now();
	}

	//Renders each object, taking in the key for the texture
	//Ends the program if an invalid key is passed in
	//Will return false if this is the case
	//Function automatically kills the program if there is an error
	m_playerObject->Render(v, s, m_cameraPosition);

	for (size_t i = 0; i < m_worldObjects.size(); i++)
	{
		m_worldObjects[i]->Render(v, s, m_cameraPosition);
	}

	m_playerHealthBar->Render(v);

	m_resumeButton->Render(v);
	m_restartButton->Render(v);
	m_quitButton->Render(v);
	HAPI.RenderText(10, 720, HAPI_TColour::WHITE, "Points: " + std::to_string(m_points), 18);
}

//Loops through each enemy in the world 
//Returns true if no enemies are found or all enemies in the world are inactive
bool World::CheckAllEnemiesDead()
{
	if (m_enemyCount <= 0 || m_map->GetCurrentRoom().GetIsCleared() == true) {
		return true;
	}

	bool allDead{ true };

	int startPoint = (int)m_worldObjects.size() - m_enemyCount - m_otherExtraInstanceCount - 1;

	if (startPoint <= 3) {
		return true;
	}

	int endPoint = (int)m_worldObjects.size() - m_otherExtraInstanceCount;

	for (int i = startPoint; i < endPoint; i++)
	{
		if (i >= m_worldObjects.size()) {
			break;
		}

		if (m_worldObjects[i]->GetIsActive() == true && m_worldObjects[i]->GetTag() == ObjectTag::E_ENEMY) {
			allDead = false;
			break;
		}
	}

	return allDead;
}

//Spawns enemies into the world
//Makes copies of pointers in the different enemy pools to do so
void World::SpawnEnemies()
{
	std::vector<Vector3> points = m_map->GetCurrentRoom().GetSpawnPoints();

	//Just spawns the boss enemy if the current room is the boss room
	if (m_map->GetCurrentRoom().GetIsBossRoom() == true) {
		m_enemyCount = 1;
		m_bossEnemy->Reset();
		m_bossEnemy->SetActive(true);
		m_bossEnemy->SetPosition(Vector3(472.0f, 344.0f, 0.0f));
		m_worldObjects.push_back(m_bossEnemy);
		return;
	}

	//Randomly decides a number of enemies to spawn
	int numberToSpawn = std::rand() % points.size();

	m_enemyCount = numberToSpawn + 1;

	for (size_t i = 0; i <= numberToSpawn; i++)
	{
		//Randomly chooses a type of enemy to spawn and spawns it at the given position
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
	}
}

//Resets the world to how it was at the start of the simulation
//All pooled objects are set to inactive
//Players health is reset
//A new map is generated
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
		if (o->GetTag() == ObjectTag::E_DOOR || o->GetTag() == ObjectTag::E_NEUTRAL) {
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

//Function runs every loop
//Removes any inactive objects that were spawned during runtime from the world vector
//Inactive enemies are left in the world so that the game can keep a track of how many enemies are dead in CheckAllEnemiesDead()
void World::CleaUpRuntimeObjects()
{
	int loopStart = (int)m_worldObjects.size() - m_otherExtraInstanceCount - 1;

	for (size_t i = loopStart; i < m_worldObjects.size(); i++)
	{
		if (m_worldObjects[i]->GetIsActive() == false && m_worldObjects[i]->GetTag() != ObjectTag::E_DOOR) {
			m_worldObjects.erase(m_worldObjects.begin() + i);
			m_otherExtraInstanceCount--;
			i--;
		}
	}
}

void World::SavePoints()
{
	std::ifstream reader("Data\\saveData.txt");

	if (!reader.is_open()) {
		HAPI.UserMessage("Could not open file for save data", "ERROR");
		HAPI.Close();
		return;
	}

	size_t highscore{ 0 };
	reader >> highscore;

	reader.close();

	if (m_points > highscore) {
		std::cout << "new score" << std::endl;
		std::ofstream writer("Data\\saveData.txt");

		if (!writer.is_open()) {
			HAPI.UserMessage("Could not open file for save data", "ERROR");
			HAPI.Close();
			return;
		}

		writer << m_points;
		writer.close();
	}
}
