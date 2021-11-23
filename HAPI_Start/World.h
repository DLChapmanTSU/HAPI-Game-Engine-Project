#pragma once
#include <memory>
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Object;

class World {
private:
	std::vector<std::shared_ptr<Object>> m_worldObjects;
	std::shared_ptr<Object> m_playerObject;
public:
	World();
	void Run();
};
