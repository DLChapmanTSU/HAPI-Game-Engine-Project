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

	std::vector<std::shared_ptr<Object>> stars;
	std::srand(time(NULL));

	//Creates 10000 stars in random positions
	for (size_t i = 0; i < 10000; i++)
	{
		stars.push_back(std::make_shared<Star>(HAPI_TColour(std::rand() % 256, std::rand() % 256, std::rand() % 256, std::rand() % 256), std::rand() % (width + 400) - 200, std::rand() % (height + 400) - 200, 500 - (std::rand() % 400)));
	}

	//std::shared_ptr<Object> player = std::make_shared<Object>(HAPI_TColour::WHITE, 300, 300, 0, true, "Data\\playerSprite.tga");
	//std::shared_ptr<Object> background = std::make_shared<Object>(HAPI_TColour::WHITE, 10, 10, 0, false);

	while (HAPI.Update()) {
		//Clears screen to black
		memset(screen, 0, (size_t)width * (size_t)height * 4);

		//Updates the position of each star and then renders them
		//If the z position reaches 0, their position is randomized on the x and y axis and set to 500 on the z axis
		//Colour is also randomized
		for (std::shared_ptr<Object> s : stars) {
			if (s->GetPosition()->GetZ() <= 0) {
				s->SetPosition(Vector3(std::rand() % (width + 400) - 200, std::rand() % (height + 400) - 200, 500));
				s->SetHue(HAPI_TColour(std::rand() % 256, std::rand() % 256, std::rand() % 256, std::rand() % 256));
			}
			else {
				s->Transform(Vector3(0.0f, 0.0f, -1.0f));
			}

			s->Render(screen, eyeDistance, height, width);
		}

		//background->Render(screen, eyeDistance, height, width);
		//player->Render(screen, eyeDistance, height, width);

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
