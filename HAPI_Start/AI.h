#pragma once
#include <HAPI_lib.h>

#include "Vector3.h"
//#include "World.h"

class World;
class Path;

enum class State {
	E_MOVING,
	E_ATTACKING,
	E_DEFENDING
};

struct AIObjectTemplate {
	Vector3 m_position;
	Vector3 m_destination;
	State m_state;
	size_t m_index;
};

class AI {
private:
	int m_mapWidth;
	int m_mapHeight;
	std::shared_ptr<World> m_world;
	std::vector<AIObjectTemplate> m_objects;
public:
	AI(World& w, int sw, int sh);
	void CalculatePaths();
};