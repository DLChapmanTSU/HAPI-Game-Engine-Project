#pragma once
#include <memory>
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Object;
class Visualisation;

class World {
private:
	std::vector<std::shared_ptr<Object>> m_worldObjects;
	std::shared_ptr<Object> m_playerObject;
	DWORD m_currentTime;
	DWORD m_lastUpdateTime;
	DWORD m_lastAnimationTime;
public:
	World();
	void Run();
private:
	void MasterRender(Visualisation& v);
};
