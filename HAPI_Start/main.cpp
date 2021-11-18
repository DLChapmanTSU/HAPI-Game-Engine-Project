/*
	HAPI Start
	----------
	This solution contains an already set up HAPI project and this main file
	
	The directory structure and main files are:

	HAPI_Start - contains the Visual Studio solution file (.sln)
		HAPI_Start - contains the Visual Studio HAPI_APP project file (.vcxproj) and source code
			HAPI - the directory with all the HAPI library files
			Data - a place to put your data files with a few sample ones provided

	Additionally in the top directory there is a batch file for creating a redistributable Demo folder

	For help using HAPI please see the Reference folder in the HAPI sub-directory
*/

#include "Object.h"
#include "Vector3.h"
#include "Visualisation.h"

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>

#include <memory>
#include <random>

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

void HorizontalLine(int x, int y, int l, int w, int h);
void VerticalLine(int x, int y, int l, int w, int h);

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down
void HAPI_Main()
{
	//Initialize screen dimensions and eyes distance from the screen
	int width{1024};
	int height{768};
	float eyeDistance{ 500.0f };
	

	if (!HAPI.Initialise(width, height, "HAPI_Screen"))
		return;

	BYTE* screen = HAPI.GetScreenPointer();

	Visualisation vis(width, height);
	vis.GenerateSprite("Data\\playerSprite.tga", "Player", 64, 64, true, 64, 64, false);
	vis.GenerateSprite("Data\\shapeTest.png", "Test", 64, 64, true, 256, 64, true);
	vis.GenerateSprite("Data\\background.tga", "Background", 256, 256, false, 256, 256, false);

	HAPI.SetShowFPS(true);

	std::shared_ptr<Object> player = std::make_shared<Object>(301.0f, 301.0f, 0.0f);
	std::shared_ptr<Object> animationTest = std::make_shared<Object>(100.0f, 100.0f, 0.0f, 4);
	std::shared_ptr<Object> background = std::make_shared<Object>(10.0f, 10.0f, 0.0f);

	DWORD lastAnimationTime = HAPI.GetTime();

	while (HAPI.Update()) {
		//Clears screen to given colour
		HAPI_TColour bgColour(10, 56, 33, 255);
		vis.ClearToColour(bgColour, 1024, 768);

		DWORD currentTime = HAPI.GetTime();

		//Updates animation if set time has elapsed
		if (currentTime - lastAnimationTime >= (DWORD)500) {
			if (animationTest->GetCurrentFrame() + 1 >= animationTest->GetMaxFrame()){
				animationTest->SetCurrentFrame(0);
			}
			else {
				animationTest->SetCurrentFrame(animationTest->GetCurrentFrame() + 1);
			}
			lastAnimationTime = HAPI.GetTime();
		}

		//Renders each object, taking in the key for the texture
		//Ends the program if an invalid key is passed in
		//Will return false if this is the case
		if (!vis.RenderTexture(background->GetPosition(), "Background", background->GetCurrentFrame())) {
			HAPI.UserMessage("Texture Does Not Exist In Visualisation", "ERROR");
			HAPI.Close();
		}

		if (!vis.RenderTexture(player->GetPosition(), "Player", player->GetCurrentFrame())) {
			HAPI.UserMessage("Texture Does Not Exist In Visualisation", "ERROR");
			HAPI.Close();
		}

		if (!vis.RenderTexture(animationTest->GetPosition(), "Test", animationTest->GetCurrentFrame())) {
			HAPI.UserMessage("Texture Does Not Exist In Visualisation", "ERROR");
			HAPI.Close();
		}
		
		/*if (!vis.RenderTexture(transparencyCheck->GetPosition(), "AlphaThing")) {
			HAPI.UserMessage("Texture Does Not Exist In Visualisation", "ERROR");
			HAPI.Close();
		}*/

		//Checks user keyboard inputs
		//If S is pressed, the eye distance is increased, drawing the eye away
		//If W is pressed, the eye distance is decreased, bringing the eye closer to the screen
		const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();

		if (keyData.scanCode['S'] && eyeDistance < 2000.0f) {
			eyeDistance++;
		}
		else if (keyData.scanCode['W'] && eyeDistance > 1.0f) {
			eyeDistance--;
		}

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

		//Stops the player from moving if they would move off the edge of the screen
		//Vector3 newPosition = playerMove + *player->GetPosition();
		//if (newPosition.GetX() < 0 || newPosition.GetX() + player->GetDimensions().first >= width || newPosition.GetY() + player->GetDimensions().second >= height || newPosition.GetY() < 0) {
		//	//Player leaving screen
		//}
		//else {
		//	player->Translate(playerMove);
		//}

		player->Translate(playerMove);

		
		
		//Displays the eye distance to the top left of the screen
		if (!HAPI.RenderText(0, 12, HAPI_TColour::WHITE, "Eye Distance: " + std::to_string((int)eyeDistance))) {
			//ERROR
		}
	}
}

void HorizontalLine(int x, int y, int l, int w, int h) {
	int startOffset = x + y * w;
	int endOffset = startOffset + l;
	BYTE* screen = HAPI.GetScreenPointer();

	for (size_t i = startOffset; i < endOffset; i++)
	{
		screen[i * 4] = 255;
	}
}

void VerticalLine(int x, int y, int l, int w, int h) {
	int startOffset = x + y * w;
	int endOffset = startOffset + (w * l);
	BYTE* screen = HAPI.GetScreenPointer();

	for (size_t i = startOffset; i < endOffset; i += w)
	{
		screen[i * 4] = 255;
	}
}
