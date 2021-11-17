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
	//Need a way to render the correct frame of an animation
	//Could have the correct frame stored in the Object and have it passed through RenderTexture() and set before clipping/rendering
	// 	   Would have to do away with Sprite::StepAnimation() for this, as this would become redundant
	//Could re-structure to let the object hold a copy of its own sprite, but that wouldn't be effecient
	bool RenderTexture(std::shared_ptr<Vector3>& p, std::string n, int f);
	void ClearPointers();
};