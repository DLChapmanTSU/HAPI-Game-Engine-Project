#pragma once
#include <memory>
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Vector3;

class Object {
protected:
	std::shared_ptr<Vector3> m_position;
	//std::string m_spriteName;
	int m_currentFrame{ 0 };
	int m_maxFrame;
public:
	Object(int x = 0, int y = 0, int z = 0, int m = 0);
	void SetPosition(Vector3& v);
	std::shared_ptr<Vector3>& GetPosition();
	void Translate(Vector3& v);
	int GetCurrentFrame() { return m_currentFrame; };
	void SetCurrentFrame(int f);
	int GetMaxFrame() { return m_maxFrame; };
};