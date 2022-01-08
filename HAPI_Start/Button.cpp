#include "Button.h"
#include "Rectangle.h"
#include "Visualisation.h"

Button::Button(Vector3& p, unsigned int w, unsigned int h, std::string m, HAPISPACE::HAPI_TColour c, bool a)
{
	m_screenPosition = p;
	m_width = w;
	m_height = h;
	m_message = m;
	m_colour = c;
	m_isActive = a;
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

void Button::Render(Visualisation& v)
{
	if (m_isActive == false) {
		return;
	}

	v.RenderDefault(m_screenPosition, m_width, m_height, m_colour);
	HAPI.RenderText(m_screenPosition.GetX(), m_screenPosition.GetY(), HAPISPACE::HAPI_TColour::BLACK, m_message);
}

void Button::SetIsActive(bool a)
{
	m_isActive = a;
}
