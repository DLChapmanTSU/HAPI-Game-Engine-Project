#include "Object.h"
#include "Vector3.h"
#include "Rectangle.h"

#include <HAPI_lib.h>

using namespace HAPISPACE;

Object::Object(std::pair<int, int> h, std::string k, float x, float y, float z, int m)
{
	m_position = std::make_shared<Vector3>(x, y, z);
	m_maxFrame = m;
	m_hitboxDimensions = h;
	m_spriteKey = k;
}

void Object::SetPosition(Vector3& v)
{
	m_position = std::make_shared<Vector3>(v);
}

std::shared_ptr<Vector3>& Object::GetPosition()
{
	return m_position;
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
		m_currentFrame = m_maxFrame - 1;
	}
	else {
		m_currentFrame = f;
	}
}

void PlayerObject::Update(bool c)
{
	//Collisions
	if (c == true) {

	}
	//Animations
}

void PlayerObject::CheckCollision(std::vector<std::shared_ptr<Object>>& o)
{
	Rectangle myHitbox(m_position->GetX(), m_position->GetX() + m_hitboxDimensions.first, m_position->GetY(), m_position->GetY() + m_hitboxDimensions.second);

	for (std::shared_ptr<Object> object : o) {
		Rectangle otherHitbox(object->GetPosition()->GetX(), object->GetPosition()->GetX() + object->GetHitbox().first, object->GetPosition()->GetY(), object->GetPosition()->GetY() + object->GetHitbox().second);

		if (myHitbox.IsOverlap(otherHitbox) == true) {
			std::cout << "Collision" << std::endl;
		}
		else {
			std::cout << "No Collision" << std::endl;
		}
	}
}

void WallObject::Update(bool c)
{
}

void WallObject::CheckCollision(std::vector<std::shared_ptr<Object>>& o)
{
	Rectangle myHitbox(m_position->GetX(), m_position->GetX() + m_hitboxDimensions.first, m_position->GetY(), m_position->GetY() + m_hitboxDimensions.second);

	for (std::shared_ptr<Object> object : o) {
		Rectangle otherHitbox(object->GetPosition()->GetX(), object->GetPosition()->GetX() + object->GetHitbox().first, object->GetPosition()->GetY(), object->GetPosition()->GetY() + object->GetHitbox().second);

		if (myHitbox.IsOverlap(otherHitbox) == true) {
			std::cout << "Collision" << std::endl;
		}
	}
}
