#pragma once
#include <HAPI_lib.h>

#include "Room.h"

struct MapCoords {
	size_t m_x;
	size_t m_y;
};

class Map {
private:
	//std::vector<Room> m_rooms;
	//std::shared_ptr<Room> m_startRoom;
	//std::shared_ptr<Room> m_currentRoom;
	size_t m_currentRoom{ 0 };
	std::vector<std::shared_ptr<Room>> m_rooms;
public:
	Map();
	void GenerateMap();
private:
	bool ConnectRoom(size_t r1, size_t r2, RoomDirection d);
};