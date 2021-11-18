#pragma once
#include <memory>
#include <map>
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Sprite;
class Vector3;

class Visualisation {
private:
	std::map<std::string, std::shared_ptr<Sprite>> m_sprites;
	int m_screenWidth;
	int m_screenHeight;
	BYTE* m_screen;
public:
	Visualisation(int w = 1024, int h = 768);
	void GenerateSprite(std::string d, std::string i, int w, int h, bool t, int aw, int ah, bool a);
	void ClearToColour(HAPI_TColour& c, int w, int h);
	bool RenderTexture(std::shared_ptr<Vector3>& p, std::string n, int f);
	void ClearPointers();
};