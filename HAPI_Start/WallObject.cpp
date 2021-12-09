#include "WallObject.h"
#include "PlayerObject.h"
#include "Vector3.h"
#include "Rectangle.h"
#include "Visualisation.h"
#include "World.h"

void WallObject::Update(World& w)
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
			//std::cout << "Collision" << std::endl;
		}
	}
}