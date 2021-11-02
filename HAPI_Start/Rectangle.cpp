#include "Rectangle.h"
#include "Vector3.h"

Rectangle::Rectangle(int l, int r, int t, int b)
{
	m_left = l;
	m_right = r;
	m_top = t;
	m_bottom = b;
}

void Rectangle::Clip(const Rectangle& r)
{
	if (m_left < r.m_left) {
		m_left = r.m_left;
	}

	if (m_right > r.m_right) {
		m_right = r.m_right;
	}

	if (m_top < r.m_top) {
		m_top = r.m_top;
	}

	if (m_bottom > r.m_bottom) {
		m_bottom = r.m_bottom;
	}
}

void Rectangle::Translate(const Vector3& v)
{
	m_left += v.GetX();
	m_right += v.GetX();
	m_top += v.GetY();
	m_bottom += v.GetY();
}
