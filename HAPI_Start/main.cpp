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

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>

#include <memory>
#include <random>

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

void HorizontalLine(int x, int y, int l, int w, int h);
void VerticalLine(int x, int y, int l, int w, int h);
void ClearToColour(HAPI_TColour& c, int w, int h);

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

	std::shared_ptr<Object> star = std::make_shared<Object>(200, 200, 500);

	HAPI.SetShowFPS(true);

	//std::vector<std::shared_ptr<Object>> stars;
	//std::srand(time(NULL));

	////Creates 10000 stars in random positions
	//for (size_t i = 0; i < 10000; i++)
	//{
	//	stars.emplace_back(std::make_shared<Star>(HAPI_TColour(std::rand() % 256, std::rand() % 256, std::rand() % 256, std::rand() % 256), std::rand() % (width + 400) - 200, std::rand() % (height + 400) - 200, 500 - (std::rand() % 400)));
	//}

	std::shared_ptr<Object> player = std::make_shared<Object>(HAPI_TColour::WHITE, 301, 301, 0, true, "Data\\playerSprite.tga");
	std::shared_ptr<Object> background = std::make_shared<Object>(HAPI_TColour::WHITE, 10, 10, 0, false, "Data\\background.tga", 256, 256);
	std::shared_ptr<Object> transparencyCheck = std::make_shared<Object>(HAPI_TColour::WHITE, 500, 500, 0, true, "Data\\alphaThing.tga");

	while (HAPI.Update()) {
		//Clears screen to given colour
		HAPI_TColour bgColour(10, 56, 33, 255);
		ClearToColour(bgColour, 1024, 768);

		//Updates the position of each star and then renders them
		//If the z position reaches 0, their position is randomized on the x and y axis and set to 500 on the z axis
		//Colour is also randomized
		/*for (std::shared_ptr<Object> &s : stars) {
			if (s->GetPosition()->GetZ() <= 0) {
				s->SetPosition(Vector3(std::rand() % (width + 400) - 200, std::rand() % (height + 400) - 200, 500));
				s->SetHue(HAPI_TColour(std::rand() % 256, std::rand() % 256, std::rand() % 256, std::rand() % 256));
			}
			else {
				s->Transform(Vector3(0.0f, 0.0f, -1.0f));
			}

			s->Render(screen, eyeDistance, height, width);
		}*/

		background->Render(screen, eyeDistance, height, width);
		
		transparencyCheck->Render(screen, eyeDistance, height, width);
		player->Render(screen, eyeDistance, height, width);

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

		playerMove.Normalize();
		player->Transform(playerMove);
		
		//Displays the eye distance to the top left of the screen
		if (!HAPI.RenderText(0, 12, HAPI_TColour::WHITE, "Eye Distance: " + std::to_string((int)eyeDistance))) {
			//ERROR
		}
	}

	player->ClearPointers();
	background->ClearPointers();
	transparencyCheck->ClearPointers();

	//delete[] screen;
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

void ClearToColour(HAPI_TColour& c, int w, int h)
{
	BYTE* screen = HAPI.GetScreenPointer();

	if (c.red == c.green && c.red == c.blue) {
		memset(screen, c.red, (size_t)w * (size_t)h * 4);
	}
	else {
		for (int i = 0; i < w * h; i++)
		{
			int offset{ i * 4 };
			screen[offset] = c.red;
			screen[offset + 1] = c.green;
			screen[offset + 2] = c.blue;
		}
	}
}
