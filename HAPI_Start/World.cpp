#include "World.h"
#include "Object.h"
#include "Vector3.h"
#include "Visualisation.h"

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>

#include <memory>
#include <random>

World::World()
{
	//Create Player
	m_playerObject = std::make_shared<PlayerObject>(std::pair<int, int>(64, 64), "Player", 301.0f, 301.0f, 0.0f);
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

	m_currentTime = HAPI.GetTime();
	m_lastUpdateTime = HAPI.GetTime();
	m_lastAnimationTime = HAPI.GetTime();
}

void World::Run()
{
	//Initialize screen dimensions and eyes distance from the screen
	int width{ 1024 };
	int height{ 768 };


	if (!HAPI.Initialise(width, height, "HAPI_Screen"))
		return;

	BYTE* screen = HAPI.GetScreenPointer();

	Visualisation vis(width, height);
	vis.GenerateSprite("Data\\playerSprite.tga", "Player", 64, 64, true, 64, 64, false);
	vis.GenerateSprite("Data\\shapeTest.png", "Test", 64, 64, true, 256, 64, true);
	vis.GenerateSprite("Data\\background.tga", "Background", 256, 256, false, 256, 256, false);

	HAPI.SetShowFPS(true);

	//std::shared_ptr<Object> player = std::make_shared<Object>(301.0f, 301.0f, 0.0f);
	//std::shared_ptr<Object> animationTest = std::make_shared<Object>(100.0f, 100.0f, 0.0f, 4);
	//std::shared_ptr<Object> background = std::make_shared<Object>(10.0f, 10.0f, 0.0f);



	while (HAPI.Update()) {
		//Clears screen to given colour
		HAPI_TColour bgColour(10, 56, 33, 255);
		vis.ClearToColour(bgColour, 1024, 768);

		//Checks user keyboard inputs
		//If S is pressed, the eye distance is increased, drawing the eye away
		//If W is pressed, the eye distance is decreased, bringing the eye closer to the screen
		const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();

		const HAPI_TControllerData& conData = HAPI.GetControllerData(0);

		Vector3 playerMove(0.0f, 0.0f, 0.0f);

		//Checks to see if the controller is plugged in
		//If it is, movement is calculated using the left thumb stick
		//Otherwise, movement is done using the arrow keys
		if (conData.isAttached) {
			//Controller Inputs
			if (conData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 10000 || conData.digitalButtons[HK_DIGITAL_DPAD_UP] == true) {
				playerMove = playerMove + Vector3(0.0f, -5.0f, 0.0f);
			}
			else if (conData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -10000 || conData.digitalButtons[HK_DIGITAL_DPAD_DOWN] == true) {
				playerMove = playerMove + Vector3(0.0f, 5.0f, 0.0f);
			}

			if (conData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 10000 || conData.digitalButtons[HK_DIGITAL_DPAD_RIGHT] == true) {
				playerMove = playerMove + Vector3(5.0f, 0.0f, 0.0f);
			}
			else if (conData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -10000 || conData.digitalButtons[HK_DIGITAL_DPAD_LEFT] == true) {
				playerMove = playerMove + Vector3(-5.0f, 0.0f, 0.0f);
			}
		}
		else {
			//Arrow Key Inputs
			if (keyData.scanCode[HK_UP]) {
				playerMove = playerMove + Vector3(0.0f, -5.0f, 0.0f);
			}

			if (keyData.scanCode[HK_DOWN]) {
				playerMove = playerMove + Vector3(0.0f, 5.0f, 0.0f);
			}

			if (keyData.scanCode[HK_RIGHT]) {
				playerMove = playerMove + Vector3(5.0f, 0.0f, 0.0f);
			}

			if (keyData.scanCode[HK_LEFT]) {
				playerMove = playerMove + Vector3(-5.0f, 0.0f, 0.0f);
			}
		}

		//Normalizes the vector before applying the translation
		playerMove.Normalize();
		m_playerObject->SetVelocity(playerMove);

		//Check collisions between each object
		m_playerObject->CheckCollision(m_worldObjects);

		m_currentTime = HAPI.GetTime();

		if (m_currentTime - m_lastUpdateTime >= (DWORD)20) {
			m_lastUpdateTime = HAPI.GetTime();
			m_playerObject->Update();
		}

		DWORD timeElapsed = m_currentTime - m_lastUpdateTime;

		std::cout << timeElapsed << std::endl;

		MasterRender(vis, timeElapsed);
	}
}

void World::MasterRender(Visualisation& v, DWORD s)
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

	float fs = (float)s;

	Vector3 lerpPosition;
	lerpPosition.Lerp(*m_playerObject->GetPosition(), *m_playerObject->GetPosition() + *m_playerObject->GetVelocity(), fs / (DWORD)20);

	std::cout << "X: " << lerpPosition.GetX() << " Y: " << lerpPosition.GetY() << std::endl;
	std::cout << (float)(s / (DWORD)100) << std::endl;

	const Vector3 lerped = lerpPosition;

	//Renders each object, taking in the key for the texture
	//Ends the program if an invalid key is passed in
	//Will return false if this is the case
	if (!v.RenderTexture(lerped, m_playerObject->GetSpriteKey(), m_playerObject->GetCurrentFrame())) {
		HAPI.UserMessage("Texture Does Not Exist In Visualisation", "ERROR");
		HAPI.Close();
	}

	for (std::shared_ptr<Object> o : m_worldObjects) {
		if (!v.RenderTexture(*o->GetPosition(), o->GetSpriteKey(), o->GetCurrentFrame())) {
			HAPI.UserMessage("Texture Does Not Exist In Visualisation", "ERROR");
			HAPI.Close();
		}
	}
}
