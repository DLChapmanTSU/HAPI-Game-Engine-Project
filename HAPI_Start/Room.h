#pragma once
#include <HAPI_lib.h>

#include "Vector3.h"

//Room will act as a node in a graph, with the map acting as the overall graph
//Map will set connections, the Room is purely for holding connection and spawn point data

class Map;

enum class RoomDirection {
	E_UP,
	E_DOWN,
	E_LEFT,
	E_RIGHT
};

struct Room {
public:
	size_t m_up{ 0 };
	size_t m_down{ 0 };
	size_t m_left{ 0 };
	size_t m_right{ 0 };
	size_t m_index;
	std::vector<Vector3> m_spawnPoints;

	friend class Map;
public:
	Room(size_t i);
};