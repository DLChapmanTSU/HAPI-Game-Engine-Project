#pragma once
#include <memory>
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Vector3;
class Visualisation;
class CharacterObject;

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
	bool m_isActive{ true };
	ObjectTag m_tag;
public:
	Object(std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0, ObjectTag t = ObjectTag::E_NEUTRAL, bool a = true);
	void SetPosition(const Vector3& v);
	const std::shared_ptr<Vector3>& GetPosition() const { return m_position; };
	void Translate(Vector3& v);
	const int GetCurrentFrame() const { return m_currentFrame; };
	void SetCurrentFrame(int f);
	const int GetMaxFrame() const { return m_maxFrame; };
	const std::pair<int, int>& GetHitbox() const { return m_hitboxDimensions; };
	const std::string& GetSpriteKey() const { return m_spriteKey; };
	const std::shared_ptr<Vector3>& GetVelocity() const { return m_velocity; };
	const ObjectTag GetTag() const { return m_tag; };
	const bool GetIsActive() const { return m_isActive; };
	void SetActive(bool a);
	void SetVelocity(const Vector3& v);
	bool Render(Visualisation& v, DWORD s);
	virtual void Update() = 0;
	virtual void CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<CharacterObject>& p) = 0;
};

class CharacterObject : public Object {
protected:
	int m_health{ 100 };
public:
	CharacterObject(std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0, ObjectTag t = ObjectTag::E_NEUTRAL, bool a = true) : Object(h, k, x, y, z, m, t, a) {};
	//virtual void Update() = 0;
	//virtual void CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<CharacterObject>& p) = 0;
	bool TakeDamage(int d = 0);
};

class PlayerObject : public CharacterObject {
public:
	PlayerObject(std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0, ObjectTag t = ObjectTag::E_NEUTRAL, bool a = true) : CharacterObject(h, k, x, y, z, m, t, a) {};
	void Update();
	void CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<CharacterObject>& p);
};

class WallObject : public Object {
public:
	WallObject(std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0, ObjectTag t = ObjectTag::E_NEUTRAL, bool a = true) : Object(h, k, x, y, z, m, t, a) {};
	void Update();
	void CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<CharacterObject>& p);
};

class BulletObject : public Object {
private:
	float m_lifeTime{ 0.0f };
public:
	BulletObject(std::pair<int, int> h, std::string k, float x = 0.0f, float y = 0.0f, float z = 0.0f, int m = 0, ObjectTag t = ObjectTag::E_NEUTRAL, bool a = true) : Object(h, k, x, y, z, m, t, a) {};
	void Update();
	void CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<CharacterObject>& p);
};