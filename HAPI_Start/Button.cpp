#include "Button.h"
#include "Rectangle.h"

Button::Button(Vector3& p, unsigned int w, unsigned int h)
{
	m_screenPosition = p;
	m_width = w;
	m_height = h;
}

bool Button::HasClick(Vector3& p)
{
	Rectangle buttonRect(m_screenPosition.GetX(), m_screenPosition.GetX() + m_width, m_screenPosition.GetY(), m_screenPosition.GetY() + m_width);

	if (p.GetX() > buttonRect.m_left && p.GetX() < buttonRect.m_right && p.GetY() > buttonRect.m_top && p.GetY() < buttonRect.m_bottom) {
		return true;
	}
	else {
		return false;
	}
}
