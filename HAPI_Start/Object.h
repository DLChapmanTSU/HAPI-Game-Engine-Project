#pragma once
#include <memory>
#include <HAPI_lib.h>

using namespace HAPISPACE;

class Vector3;

class Object {
protected:
	std::shared_ptr<Vector3> m_position;
	int m_sizeX;
	int m_sizeY;
public:
	Object(int x = 0, int y = 0, int z = 0, int sx = 64, int sy = 64);
	void SetPosition(Vector3& v);
	std::shared_ptr<Vector3>& GetPosition();
	void Translate(Vector3& v);
	std::pair<int, int> GetDimensions() const;
};