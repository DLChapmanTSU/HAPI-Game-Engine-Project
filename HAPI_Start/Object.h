#pragma once
#include <memory>
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Vector3;

enum class ObjectTag {
	E_FRIENDLY,
	E_ENEMY,
	E_NEUTRAL
};

class Object {
protected:
	std::shared_ptr<Vector3> m_position;
	std::shared_ptr<Vector3> m_velocity;
	float m_moveSpeed{ 5.0f };
	int m_currentFrame{ 0 };
	int m_maxFrame;
	std::pair<int, int> m_hitboxDimensions;
	std::string m_spriteKey;
public:
	Object(std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0);
	void SetPosition(const Vector3& v);
	const std::shared_ptr<Vector3>& GetPosition() const { return m_position; };
	void Translate(Vector3& v);
	const int GetCurrentFrame() const { return m_currentFrame; };
	void SetCurrentFrame(int f);
	const int GetMaxFrame() const { return m_maxFrame; };
	const std::pair<int, int>& GetHitbox() const { return m_hitboxDimensions; };
	const std::string& GetSpriteKey() const { return m_spriteKey; };
	const std::shared_ptr<Vector3>& GetVelocity() const { return m_velocity; };
	void SetVelocity(const Vector3& v);
	virtual void Update() = 0;
	virtual void CheckCollision(std::vector<std::shared_ptr<Object>>& o) = 0;
};

class PlayerObject : public Object {
public:
	PlayerObject(std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0) : Object(h, k, x, y, z, m) {};
	void Update();
	void CheckCollision(std::vector<std::shared_ptr<Object>>& o);
};

class WallObject : public Object {
public:
	WallObject(std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0) : Object(h, k, x, y, z, m) {};
	void Update();
	void CheckCollision(std::vector<std::shared_ptr<Object>>& o);
};