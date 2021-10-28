#pragma once
#include <memory>
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Vector3;

class Object {
protected:
	std::shared_ptr<Vector3> m_position;
	int m_sizeX;
	int m_sizeY;
	//HAPI_TColour m_hue{ HAPI_TColour::RED };
	//BYTE* m_texture;
	//int m_textureWidth;
	//int m_textureHeight;
	//bool m_hasTransparency{ false };
public:
	Object(int x = 0, int y = 0, int z = 0, int sx = 64, int sy = 64);
	//virtual void Render(BYTE*& s, float d = 1.0f, float h = 768.0f, float w = 1024.0f);
	void SetPosition(Vector3& v);
	std::shared_ptr<Vector3>& GetPosition();
	void Translate(Vector3& v);
	//void SetHue(HAPI_TColour& c);
	//void ClearPointers();
	std::pair<int, int> GetDimensions() const;
};

//class Star : public Object {
//public:
//	Star(HAPI_TColour sc, int sx = 0, int sy = 0, int sz = 0) : Object(sc, sx, sy, sz) {};
//	void Render(BYTE*& s, float d = 1.0f, float h = 768.0f, float w = 1024.0f);
//private:
//	int StarSize();
//};