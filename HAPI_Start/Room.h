#pragma once
#include <HAPI_lib.h>

#include "Vector3.h"

//Room will act as a node in a graph, with the map acting as the overall graph
//Map will set connections, the Room is purely for holding connection and spawn point data

enum class RoomDirection {
	E_UP,
	E_DOWN,
	E_LEFT,
	E_RIGHT
};

struct Room {
private:
	std::shared_ptr<Room> m_up;
	std::shared_ptr<Room> m_down;
	std::shared_ptr<Room> m_left;
	std::shared_ptr<Room> m_right;
	std::vector<Vector3> m_spawnPoints;
	unsigned int m_index;
public:
	Room(std::vector<Vector3>& s, unsigned int i);
};