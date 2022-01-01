#include "AI.h"
#include "World.h"

AI::AI(World& w, int sw, int sh)
{
	m_world = std::make_shared<World>(w);
	m_mapWidth = sw;
	m_mapHeight = sh;
}

void AI::CalculatePaths()
{
	if (m_objects.size() == 0) {
		return;
	}

	for (AIObjectTemplate o : m_objects) {
		o.m_position = m_world->GetEnemyPosition(o.m_index);

		Vector3 destination;
		destination.SetX(std::rand() % (m_mapWidth - 128) + 64);
		destination.SetY(std::rand() % (m_mapHeight - 128) + 64);

		o.m_state = State::E_MOVING;

		Vector3 pathToDestination = destination - o.m_position;

		pathToDestination.Normalize();

		m_world->SetAIVelocity(o.m_index, pathToDestination);
	}
}
