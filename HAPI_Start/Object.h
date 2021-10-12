#pragma once
#include <memory>
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Vector3;

class Object {
protected:
	std::shared_ptr<Vector3> m_position;
	HAPI_TColour m_hue{ HAPI_TColour::RED };
	std::string m_sprite;
	bool m_hasTransparency{ false };
public:
	Object(HAPI_TColour c, int x = 0, int y = 0, int z = 0, bool t = false, std::string s = "Data\\background.tga");
	virtual void Render(BYTE*& s, float d = 1.0f, float h = 768.0f, float w = 1024.0f);
	void SetPosition(Vector3& v);
	std::shared_ptr<Vector3>& GetPosition();
	void Transform(Vector3& v);
	void SetHue(HAPI_TColour& c);
};

class Star : public Object {
public:
	Star(HAPI_TColour sc, int sx = 0, int sy = 0, int sz = 0) : Object(sc, sx, sy, sz) {};
	void Render(BYTE*& s, float d = 1.0f, float h = 768.0f, float w = 1024.0f);
private:
	int StarSize();
};