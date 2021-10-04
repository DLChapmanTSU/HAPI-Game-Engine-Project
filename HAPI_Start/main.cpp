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

#include <memory>

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
	int pixelTarget{ 0 };
	

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

	//HAPI.SetShowFPS(true);

	

	while (HAPI.Update()) {
		//HAPI.RenderText(100, 100, HAPI_TColour::BLUE, "I am HAPI", 50);
		//HAPI.RenderText(500, 500, HAPI_TColour::RED, HAPI_TColour::WHITE, 5.0f, "Happy is fun!", 50);
		//memset(screen, 0, width * height * 4);

		star->Render(screen, 100.0f);
		
		//std::shared_ptr<Vector3> pos = star->GetPosition();
		//if (pos->GetZ() >= 1) {
		//	int posZ = pos->GetZ();
		//	posZ--;
		//	pos->SetZ(posZ);
		//}
		//else {
		//	pos->SetZ(10);
		//}
		//star->SetPosition(*pos);
		

		//HAPI.SetControllerRumble(0, 65535, 65535);
		//if ((pixelTarget * 4) < (width * height * 4)) {
		//	screen[pixelTarget * 4] = 0;
		//	screen[(pixelTarget * 4) + 1] = 255;
		//	screen[(pixelTarget * 4) + 2] = 0;
		//	pixelTarget++;
		//}
		
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
