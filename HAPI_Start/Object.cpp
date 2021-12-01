#include "Object.h"
#include "Vector3.h"
#include "Rectangle.h"
#include "Visualisation.h"

#include <HAPI_lib.h>

using namespace HAPISPACE;

Object::Object(std::pair<int, int> h, std::string k, float x, float y, float z, int m, ObjectTag t, bool a)
{
	m_position = std::make_shared<Vector3>(x, y, z);
	m_velocity = std::make_shared<Vector3>(0.0f, 0.0f, 0.0f);
	m_maxFrame = m;
	m_hitboxDimensions = h;
	m_spriteKey = k;
	m_tag = t;
	m_isActive = a;
}

void Object::SetPosition(const Vector3& v)
{
	m_position = std::make_shared<Vector3>(v);
}

void Object::Translate(Vector3& v)
{
	Vector3 temp = *m_position;
	temp = temp + v;
	m_position = std::make_shared<Vector3>(temp);
}

void Object::SetCurrentFrame(int f)
{
	if (f < 0) {
		m_currentFrame = 0;
	}
	else if (f >= m_maxFrame) {
		m_currentFrame = 0;
	}
	else {
		m_currentFrame = f;
	}
}

void Object::SetActive(bool a)
{
	m_isActive = a;
}

void Object::SetVelocity(const Vector3& v)
{
	Vector3 newVelocity = v;
	m_velocity = std::make_shared<Vector3>(newVelocity * m_moveSpeed);
}

bool Object::Render(Visualisation& v, DWORD s)
{
	if (m_isActive == false) {
		return true;
	}

	float fs = (float)s;

	Vector3 lerpPosition;
	lerpPosition.Lerp(*m_position, *m_position + *m_velocity, fs / (DWORD)20);

	std::cout << "X: " << lerpPosition.GetX() << " Y: " << lerpPosition.GetY() << std::endl;
	std::cout << (float)(s / (DWORD)100) << std::endl;

	const Vector3 lerped = lerpPosition;

	if (!v.RenderTexture(lerped, m_spriteKey, m_currentFrame)) {
		HAPI.UserMessage("Texture Does Not Exist In Visualisation", "ERROR");
		HAPI.Close();
		return false;
	}

	return true;
}

void PlayerObject::Update()
{
	//Update position
	Translate(*m_velocity);
}

void PlayerObject::CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<CharacterObject>& p)
{
	Rectangle myHitbox(m_position->GetX(), m_position->GetX() + m_hitboxDimensions.first, m_position->GetY(), m_position->GetY() + m_hitboxDimensions.second);

	for (std::shared_ptr<Object> object : o) {
		Rectangle otherHitbox(object->GetPosition()->GetX(), object->GetPosition()->GetX() + object->GetHitbox().first, object->GetPosition()->GetY(), object->GetPosition()->GetY() + object->GetHitbox().second);

		if (myHitbox.IsOverlap(otherHitbox) == true) {
			//std::cout << "Collision" << std::endl;
		}
		else {
			//std::cout << "No Collision" << std::endl;
		}
	}
}

void WallObject::Update()
{
	//Walls don't need to update
}

void WallObject::CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<CharacterObject>& p)
{
	Rectangle myHitbox(m_position->GetX(), m_position->GetX() + m_hitboxDimensions.first, m_position->GetY(), m_position->GetY() + m_hitboxDimensions.second);

	for (std::shared_ptr<Object> object : o) {
		Rectangle otherHitbox(object->GetPosition()->GetX(), object->GetPosition()->GetX() + object->GetHitbox().first, object->GetPosition()->GetY(), object->GetPosition()->GetY() + object->GetHitbox().second);

		if (myHitbox.IsOverlap(otherHitbox) == true) {
			std::cout << "Collision" << std::endl;
		}
	}
}

void BulletObject::Update()
{
	if (m_lifeTime >= 10.0f) {
		m_lifeTime = 0.0f;
		m_isActive = false;
		return;
	}

	//Update position
	Translate(*m_velocity);

	m_lifeTime += 0.1f;
}

void BulletObject::CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<CharacterObject>& p)
{
	Rectangle myHitbox(m_position->GetX(), m_position->GetX() + m_hitboxDimensions.first, m_position->GetY(), m_position->GetY() + m_hitboxDimensions.second);

	for (std::shared_ptr<Object> object : o) {
		Rectangle otherHitbox(object->GetPosition()->GetX(), object->GetPosition()->GetX() + object->GetHitbox().first, object->GetPosition()->GetY(), object->GetPosition()->GetY() + object->GetHitbox().second);

		if (myHitbox.IsOverlap(otherHitbox) == true && object->GetTag() != m_tag && object->GetIsActive() == true) {
			std::cout << "Collision" << std::endl;
			m_isActive = false;
			return;
		}
	}

	if (m_tag != ObjectTag::E_FRIENDLY) {
		Rectangle otherHitbox(p->GetPosition()->GetX(), p->GetPosition()->GetX() + p->GetHitbox().first, p->GetPosition()->GetY(), p->GetPosition()->GetY() + p->GetHitbox().second);

		if (myHitbox.IsOverlap(otherHitbox) == true && p->GetTag() != m_tag && p->GetIsActive() == true) {
			std::cout << "Character Hit" << std::endl;
			m_isActive = false;
			p->TakeDamage(1);
		}
	}
}

bool CharacterObject::TakeDamage(int d)
{
	m_health -= d;

	if (m_health <= 0) {
		m_isActive = false;
		return true;
	}
	return false;
}
