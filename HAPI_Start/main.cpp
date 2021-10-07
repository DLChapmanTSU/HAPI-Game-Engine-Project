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
	int width{1024};
	int height{768};
	//int pixelTarget{ 0 };
	float eyeDistance{ 500.0f };
	

	if (!HAPI.Initialise(width, height, "HAPI_Screen"))
		return;

	BYTE* screen = HAPI.GetScreenPointer();

	std::shared_ptr<Object> star = std::make_shared<Object>(200, 200, 500);

	//for (size_t i = 0; i < 786432; i++)
	//{
	//	if (i % 5 == 0) {
	//		int offset = i * 4;
	//		screen[offset] = 255;
	//		screen[offset + 1] = 0;
	//		screen[offset + 2] = 255;
	//	}
	//	
	//}

	HAPI.SetShowFPS(true);

	std::vector<std::shared_ptr<Object>> stars;
	std::srand(time(NULL));

	for (size_t i = 0; i < 10000; i++)
	{
		stars.push_back(std::make_shared<Star>(HAPI_TColour(std::rand() % 256, std::rand() % 256, std::rand() % 256, std::rand() % 256), std::rand() % width, std::rand() % height, 500 - (std::rand() % 100)));
	}

	

	while (HAPI.Update()) {

		memset(screen, 0, (size_t)width * (size_t)height * 4);

		for (std::shared_ptr<Object> s : stars) {
			if (s->GetPosition()->GetZ() <= 0) {
				s->SetPosition(Vector3(std::rand() % width, std::rand() % height, 500 - (std::rand() % 100)));
				s->SetHue(HAPI_TColour(std::rand() % 256, std::rand() % 256, std::rand() % 256, std::rand() % 256));
			}
			else {
				s->Transform(Vector3(0.0f, 0.0f, -1.0f));
			}

			s->Render(screen, eyeDistance, height, width);
		}

		const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();

		if (keyData.scanCode['S'] && eyeDistance < 2000.0f) {
			eyeDistance++;
		}
		else if (keyData.scanCode['W'] && eyeDistance > 1.0f) {
			eyeDistance--;
		}
		
		if (!HAPI.RenderText(0, 12, HAPI_TColour::WHITE, "Eye Distance: " + std::to_string((int)eyeDistance))) {
			//ERROR
		}

		//star->Render(screen, 100.0f);
		
		
		
		//HorizontalLine(255, 500, 200, width, height);
		//VerticalLine(35, 35, 50, width, height);
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
