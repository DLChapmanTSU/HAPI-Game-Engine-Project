#include "Map.h"
#include "Vector3.h"

#include <iostream>

Map::Map()
{

}

void Map::GenerateMap()
{
	m_rooms.clear();

	for (size_t i = 1; i <= 10; i++)
	{
		m_rooms.push_back(std::make_shared<Room>(i));
	}

	ConnectRoom(1, 2, RoomDirection::E_UP);
	ConnectRoom(1, 3, RoomDirection::E_DOWN);
	ConnectRoom(1, 4, RoomDirection::E_LEFT);
	ConnectRoom(1, 5, RoomDirection::E_RIGHT);

	int connectionsMade{ 0 };

	while (connectionsMade < 10)
	{
		int r1Rand = std::rand() % 4 + 2;
		int r2Rand = std::rand() % 5 + 6;
		if (!ConnectRoom(r1Rand, r2Rand, RoomDirection(std::rand() % 4)) && connectionsMade > 0) {
			connectionsMade--;
		}
		else {
			connectionsMade++;
		}
	}

	std::cout << "Generated Map" << std::endl;
}

bool Map::ConnectRoom(size_t r1, size_t r2, RoomDirection d)
{
	switch (d)
	{
	case RoomDirection::E_UP:
		if (m_rooms[r1 - 1]->m_up == 0 && m_rooms[r2 - 1]->m_down == 0) {
			m_rooms[r1 - 1]->m_up = m_rooms[r2 - 1]->m_index;
			m_rooms[r2 - 1]->m_down = m_rooms[r1 - 1]->m_index;
		}
		break;
	case RoomDirection::E_DOWN:
		if (m_rooms[r1 - 1]->m_down == 0 && m_rooms[r2 - 1]->m_up == 0) {
			m_rooms[r1 - 1]->m_down = m_rooms[r2 - 1]->m_index;
			m_rooms[r2 - 1]->m_up = m_rooms[r1 - 1]->m_index;
		}
		break;
	case RoomDirection::E_LEFT:
		if (m_rooms[r1 - 1]->m_left == 0 && m_rooms[r2 - 1]->m_right == 0) {
			m_rooms[r1 - 1]->m_left = m_rooms[r2 - 1]->m_index;
			m_rooms[r2 - 1]->m_right = m_rooms[r1 - 1]->m_index;
		}
		break;
	case RoomDirection::E_RIGHT:
		if (m_rooms[r1 - 1]->m_right == 0 && m_rooms[r2 - 1]->m_left == 0) {
			m_rooms[r1 - 1]->m_right = m_rooms[r2 - 1]->m_index;
			m_rooms[r2 - 1]->m_left = m_rooms[r1 - 1]->m_index;
		}
		break;
	default:
		return false;
		break;
	}
	return true;
}
