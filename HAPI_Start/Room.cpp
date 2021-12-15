#include "Room.h"

Room::Room(size_t i)
{
	m_spawnPoints.push_back(Vector3(256.0f, 192.0f, 0.0f));
	m_spawnPoints.push_back(Vector3(768.0f, 576.0f, 0.0f));
	m_spawnPoints.push_back(Vector3(256.0f, 576.0f, 0.0f));
	m_spawnPoints.push_back(Vector3(768.0f, 192.0f, 0.0f));
	m_spawnPoints.push_back(Vector3(512.0f, 384.0f, 0.0f));
	m_index = i;
}