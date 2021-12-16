#include "Map.h"
#include "Vector3.h"

#include <iostream>

Map::Map()
{
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			m_rooms[1][j] = Room();
		}
	}
}

void Map::GenerateMap()
{
	//m_rooms.clear();

	m_rooms[m_currentRoomY][m_currentRoomX].m_up = true;
	m_rooms[m_currentRoomY][m_currentRoomX].m_down = true;
	m_rooms[m_currentRoomY][m_currentRoomX].m_left = true;
	m_rooms[m_currentRoomY][m_currentRoomX].m_right = true;

	m_rooms[m_currentRoomY + 1][m_currentRoomX].m_up = true;
	m_rooms[m_currentRoomY - 1][m_currentRoomX].m_down = true;
	m_rooms[m_currentRoomY][m_currentRoomX + 1].m_left = true;
	m_rooms[m_currentRoomY][m_currentRoomX - 1].m_right = true;

	int connectionsMade{ 0 };

	while (connectionsMade < 10)
	{
		int xRand = std::rand() % 5;
		int yRand = std::rand() % 5;
		
		RoomDirection dirRand = RoomDirection(std::rand() % 4);

		switch (dirRand)
		{
		case RoomDirection::E_UP:
			if (yRand - 1 < 0) {
				break;
			}

			if (m_rooms[yRand][xRand].m_up == false && m_rooms[yRand - 1][xRand].IsReachable() == true) {
				m_rooms[yRand][xRand].m_up = true;
				m_rooms[yRand - 1][xRand].m_down = true;
				connectionsMade++;
			}
			break;
		case RoomDirection::E_DOWN:
			if (yRand + 1 >= 5) {
				break;
			}

			if (m_rooms[yRand][xRand].m_down == false && m_rooms[yRand + 1][xRand].IsReachable() == true) {
				m_rooms[yRand][xRand].m_down = true;
				m_rooms[yRand + 1][xRand].m_up = true;
				connectionsMade++;
			}
			break;
		case RoomDirection::E_LEFT:
			if (xRand - 1 < 0) {
				break;
			}

			if (m_rooms[yRand][xRand].m_left == false && m_rooms[yRand][xRand - 1].IsReachable() == true) {
				m_rooms[yRand][xRand].m_left = true;
				m_rooms[yRand][xRand - 1].m_right = true;
				connectionsMade++;
			}
			break;
		case RoomDirection::E_RIGHT:
			if (xRand + 1 >= 5) {
				break;
			}

			if (m_rooms[yRand][xRand].m_right == false && m_rooms[yRand][xRand + 1].IsReachable() == true) {
				m_rooms[yRand][xRand].m_right = true;
				m_rooms[yRand][xRand + 1].m_left = true;
				connectionsMade++;
			}
			break;
		default:
			break;
		}
	}

	std::cout << "Generated Map" << std::endl;

	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			if (m_rooms[i][j].IsReachable() == true) {
				std::cout << "1";
			}
			else {
				std::cout << "0";
			}
		}

		std::cout << std::endl;
	}
}
