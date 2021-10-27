#pragma once
#include <memory>
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Vector3;

class Object {
protected:
	std::shared_ptr<Vector3> m_position;
	//HAPI_TColour m_hue{ HAPI_TColour::RED };
	//BYTE* m_texture;
	//int m_textureWidth;
	//int m_textureHeight;
	//bool m_hasTransparency{ false };
public:
	Object(int x = 0, int y = 0, int z = 0);
	//virtual void Render(BYTE*& s, float d = 1.0f, float h = 768.0f, float w = 1024.0f);
	void SetPosition(Vector3& v);
	std::shared_ptr<Vector3>& GetPosition();
	void Translate(Vector3& v);
	//void SetHue(HAPI_TColour& c);
	//void ClearPointers();
};

//class Star : public Object {
//public:
//	Star(HAPI_TColour sc, int sx = 0, int sy = 0, int sz = 0) : Object(sc, sx, sy, sz) {};
//	void Render(BYTE*& s, float d = 1.0f, float h = 768.0f, float w = 1024.0f);
//private:
//	int StarSize();
//};