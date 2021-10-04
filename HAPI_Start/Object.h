#pragma once
#include <memory>
#include <HAPI_lib.h>

using namespace HAPISPACE;

struct Vector3;

class Object {
private:
	std::shared_ptr<Vector3> m_position;
public:
	Object(int x = 0, int y = 0, int z = 0);
	void Render(BYTE* s, float d = 1.0f);
	void SetPosition(Vector3& v);
	std::shared_ptr<Vector3>& GetPosition();
};