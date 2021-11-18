#pragma once
#include <memory>
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Vector3;

class Object {
protected:
	std::shared_ptr<Vector3> m_position;
	int m_currentFrame{ 0 };
	int m_maxFrame;
public:
	Object(float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0);
	void SetPosition(Vector3& v);
	std::shared_ptr<Vector3>& GetPosition();
	void Translate(Vector3& v);
	int GetCurrentFrame() { return m_currentFrame; };
	void SetCurrentFrame(int f);
	int GetMaxFrame() { return m_maxFrame; };
};

class PlayerObject : public Object {

};