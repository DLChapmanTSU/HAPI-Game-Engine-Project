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
	std::pair<int, int> m_hitboxDimensions;
	std::string m_spriteKey;
public:
	Object(std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0);
	void SetPosition(Vector3& v);
	std::shared_ptr<Vector3>& GetPosition();
	void Translate(Vector3& v);
	int GetCurrentFrame() { return m_currentFrame; };
	void SetCurrentFrame(int f);
	int GetMaxFrame() { return m_maxFrame; };
	const std::pair<int, int>& GetHitbox() const { return m_hitboxDimensions; };
	std::string& GetSpriteKey() { return m_spriteKey; };
	virtual void Update(bool c = false) = 0;
	virtual void CheckCollision(std::vector<std::shared_ptr<Object>>& o) = 0;
};

class PlayerObject : public Object {
public:
	PlayerObject(std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0) : Object(h, k, x, y, z, m) {};
	void Update(bool c = false);
	void CheckCollision(std::vector<std::shared_ptr<Object>>& o);
};

class WallObject : public Object {
public:
	WallObject(std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0) : Object(h, k, x, y, z, m) {};
	void Update(bool c = false);
	void CheckCollision(std::vector<std::shared_ptr<Object>>& o);
};