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
	//Sets current frame of the animation
	//Loops back to the first frame if "f" is too large
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

bool Object::Render(Visualisation& v, float s)
{
	//Won't render if the object is inactive
	if (m_isActive == false) {
		return true;
	}

	//Lerps the object between where it was the previous update and where it will be the next update
	//float fs = (float)s;

	Vector3 lerpPosition;
	lerpPosition.Lerp(*m_position, *m_position + *m_velocity, s);

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
	//Checks user keyboard inputs
		//If S is pressed, the eye distance is increased, drawing the eye away
		//If W is pressed, the eye distance is decreased, bringing the eye closer to the screen
	const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();

	const HAPI_TControllerData& conData = HAPI.GetControllerData(0);

	Vector3 playerMove(0.0f, 0.0f, 0.0f);

	//Checks to see if the controller is plugged in
	//If it is, movement is calculated using the left thumb stick
	//Otherwise, movement is done using the arrow keys
	if (conData.isAttached) {
		//Controller Inputs
		if (conData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > 10000 || conData.digitalButtons[HK_DIGITAL_DPAD_UP] == true) {
			playerMove = playerMove + Vector3(0.0f, -5.0f, 0.0f);
		}
		else if (conData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -10000 || conData.digitalButtons[HK_DIGITAL_DPAD_DOWN] == true) {
			playerMove = playerMove + Vector3(0.0f, 5.0f, 0.0f);
		}

		if (conData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > 10000 || conData.digitalButtons[HK_DIGITAL_DPAD_RIGHT] == true) {
			playerMove = playerMove + Vector3(5.0f, 0.0f, 0.0f);
		}
		else if (conData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -10000 || conData.digitalButtons[HK_DIGITAL_DPAD_LEFT] == true) {
			playerMove = playerMove + Vector3(-5.0f, 0.0f, 0.0f);
		}
	}
	else {
		//Arrow Key Inputs
		if (keyData.scanCode[HK_UP]) {
			playerMove = playerMove + Vector3(0.0f, -5.0f, 0.0f);
		}

		if (keyData.scanCode[HK_DOWN]) {
			playerMove = playerMove + Vector3(0.0f, 5.0f, 0.0f);
		}

		if (keyData.scanCode[HK_RIGHT]) {
			playerMove = playerMove + Vector3(5.0f, 0.0f, 0.0f);
		}

		if (keyData.scanCode[HK_LEFT]) {
			playerMove = playerMove + Vector3(-5.0f, 0.0f, 0.0f);
		}
	}

	//Normalizes the vector before applying the translation
	playerMove.Normalize();
	*m_velocity = playerMove;

	//Update position
	Translate(*m_velocity * m_moveSpeed);
}

void PlayerObject::CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<CharacterObject>& p)
{
	//Checks for any collisions using rectangles
	//Will handle behaviour such as snapping back when running into a wall
	Rectangle myHitbox((int)m_position->GetX(), (int)m_position->GetX() + m_hitboxDimensions.first, (int)m_position->GetY(), (int)m_position->GetY() + m_hitboxDimensions.second);

	for (std::shared_ptr<Object> object : o) {
		Rectangle otherHitbox((int)object->GetPosition()->GetX(), (int)object->GetPosition()->GetX() + object->GetHitbox().first, (int)object->GetPosition()->GetY(), (int)object->GetPosition()->GetY() + object->GetHitbox().second);

		if (myHitbox.IsOverlap(otherHitbox) == true) {
			std::cout << "Collision" << std::endl;
		}
		else {
			std::cout << "No Collision" << std::endl;
		}
	}
}

void WallObject::Update()
{
	//Walls don't need to update
}

void WallObject::CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::shared_ptr<CharacterObject>& p)
{
	//Checks for any collisions using rectangles
	Rectangle myHitbox((int)m_position->GetX(), (int)m_position->GetX() + m_hitboxDimensions.first, (int)m_position->GetY(), (int)m_position->GetY() + m_hitboxDimensions.second);

	for (std::shared_ptr<Object> object : o) {
		Rectangle otherHitbox((int)object->GetPosition()->GetX(), (int)object->GetPosition()->GetX() + object->GetHitbox().first, (int)object->GetPosition()->GetY(), (int)object->GetPosition()->GetY() + object->GetHitbox().second);

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
	//Checks for any collisions using rectangles
	//Handles killing itself and damaging characters with a different tag
	Rectangle myHitbox((int)m_position->GetX(), (int)m_position->GetX() + m_hitboxDimensions.first, (int)m_position->GetY(), (int)m_position->GetY() + m_hitboxDimensions.second);

	for (std::shared_ptr<Object> object : o) {
		Rectangle otherHitbox((int)object->GetPosition()->GetX(), (int)object->GetPosition()->GetX() + object->GetHitbox().first, (int)object->GetPosition()->GetY(), (int)object->GetPosition()->GetY() + object->GetHitbox().second);

		if (myHitbox.IsOverlap(otherHitbox) == true && object->GetTag() != m_tag && object->GetIsActive() == true) {
			std::cout << "Collision" << std::endl;
			m_isActive = false;
			return;
		}
	}

	if (m_tag != ObjectTag::E_FRIENDLY) {
		Rectangle otherHitbox((int)p->GetPosition()->GetX(), (int)p->GetPosition()->GetX() + p->GetHitbox().first, (int)p->GetPosition()->GetY(), (int)p->GetPosition()->GetY() + p->GetHitbox().second);

		if (myHitbox.IsOverlap(otherHitbox) == true && p->GetTag() != m_tag && p->GetIsActive() == true) {
			std::cout << "Character Hit" << std::endl;
			m_isActive = false;
			p->TakeDamage(1);
		}
	}
}

bool CharacterObject::TakeDamage(int d)
{
	//Reduces the players health and sets to inactive if health reaches 0
	m_health -= d;

	if (m_health <= 0) {
		m_isActive = false;
		return true;
	}
	return false;
}
