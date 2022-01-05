#include "PlayerObject.h"
#include "Vector3.h"
#include "Rectangle.h"
#include "Visualisation.h"
#include "World.h"

PlayerObject::PlayerObject(std::pair<int, int> h, std::string k, float x, float y, float z, int m, ObjectTag t, bool a) : Object(h, k, x, y, z, m, t, a)
{
	m_moveSpeed = 10.0f;
}

void PlayerObject::Update(World& w)
{
	if (m_isActive == false) {
		return;
	}

	m_currentTime = HAPI.GetTime();

	//Checks user keyboard inputs
		//If S is pressed, the eye distance is increased, drawing the eye away
		//If W is pressed, the eye distance is decreased, bringing the eye closer to the screen
	const HAPI_TKeyboardData& keyData = HAPI.GetKeyboardData();

	const HAPI_TControllerData& conData = HAPI.GetControllerData(0);

	const HAPI_TMouseData& mouseData = HAPI.GetMouseData();

	Vector3 playerMove(0.0f, 0.0f, 0.0f);
	Vector3 target(0.0f, 0.0f, 0.0f);

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

		Vector3 aimPos = Vector3(conData.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_X], -conData.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_Y], 0.0f);
		//aimPos.Normalize();

		target = aimPos - *m_position;
		target.Normalize();

		if (conData.digitalButtons[HK_DIGITAL_X] == true && (m_currentTime - m_shotTime) >= m_shotCooldown) {
			std::cout << "X: " << target.GetX() << " Y: " << target.GetY() << std::endl;
			w.SpawnBullet(*m_position, target, m_tag);
			m_shotTime = HAPI.GetTime();
			std::cout << "PEW" << std::endl;
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

		Vector3 mousePos = Vector3(mouseData.x, mouseData.y, 0.0f);
		target = mousePos - *m_position;
		target.Normalize();

		if (mouseData.leftButtonDown && (m_currentTime - m_shotTime) >= m_shotCooldown) {
			w.SpawnBullet(*m_position, target, m_tag);
			m_shotTime = HAPI.GetTime();
		}
	}

	//Normalizes the vector before applying the translation
	playerMove.Normalize();
	*m_velocity = playerMove;

	//Update position
	Translate(*m_velocity * m_moveSpeed);
}

void PlayerObject::CheckCollision(std::vector<std::shared_ptr<Object>>& o, std::vector<std::shared_ptr<EnemyObject>>& e, std::shared_ptr<PlayerObject>& p, World& w)
{
	//Checks for any collisions using rectangles
	//Will handle behaviour such as snapping back when running into a wall
	Rectangle myHitbox((int)m_position->GetX(), (int)m_position->GetX() + m_hitboxDimensions.first, (int)m_position->GetY(), (int)m_position->GetY() + m_hitboxDimensions.second);

	for (std::shared_ptr<Object> object : o) {
		if (object->GetIsActive() == false) {
			continue;
		}

		Rectangle otherHitbox((int)object->GetPosition()->GetX(), (int)object->GetPosition()->GetX() + object->GetHitbox().first, (int)object->GetPosition()->GetY(), (int)object->GetPosition()->GetY() + object->GetHitbox().second);

		if (myHitbox.IsOverlap(otherHitbox) == true) {
			/*std::shared_ptr<CharacterObject> enemy;

			if (object->GetTag() == ObjectTag::E_ENEMY) {
				enemy = std::make_shared<CharacterObject>(std::dynamic_pointer_cast<CharacterObject>(object));
			}*/

			switch (object->GetTag())
			{
			case ObjectTag::E_FRIENDLY:
				break;
			case ObjectTag::E_ENEMY:
				//enemy->TakeDamage(1);
				break;
			case ObjectTag::E_NEUTRAL:
				SetPosition(*m_position - (*m_velocity * m_moveSpeed));
				/*if (myHitbox.m_right > otherHitbox.m_left && myHitbox.m_right < otherHitbox.m_right) {
					SetPosition(*m_position - Vector3(myHitbox.m_right - otherHitbox.m_left, 0.0f, 0.0f));
				}
				else if (myHitbox.m_left < otherHitbox.m_right && myHitbox.m_left > otherHitbox.m_left) {
					SetPosition(*m_position + Vector3(otherHitbox.m_right - myHitbox.m_left, 0.0f, 0.0f));
				}
				else if (myHitbox.m_bottom > otherHitbox.m_top && myHitbox.m_bottom < otherHitbox.m_bottom) {
					SetPosition(*m_position - Vector3(0.0f, myHitbox.m_bottom - otherHitbox.m_top, 0.0f));
				}
				else if (myHitbox.m_top < otherHitbox.m_bottom && myHitbox.m_top > otherHitbox.m_top) {
					SetPosition(*m_position + Vector3(0.0f, otherHitbox.m_bottom - myHitbox.m_top, 0.0f));
				}*/
				break;
			case ObjectTag::E_DOOR:
				//std::shared_ptr<Object> door = object;
				//door = std::dynamic_pointer_cast<DoorObject>(door);
				//w.MoveRoom(std::make_shared<DoorObject>(std::dynamic_pointer_cast<DoorObject>(object)));
				break;
			default:
				break;
			}
		}
		else {
			//std::cout << "No Collision" << std::endl;
		}
	}
}