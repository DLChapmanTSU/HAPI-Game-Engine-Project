#include "StatBar.h"
#include "Visualisation.h"

StatBar::StatBar(Vector3& p, float m, HAPISPACE::HAPI_TColour& c)
{
	m_screenPosition = p;
	m_maxValue = m;
	m_currentValue = m;
	//m_spriteKey = k;
	m_colour = c;
}

void StatBar::SetValue(unsigned int n)
{
	if (n > m_maxValue) {
		n = m_maxValue;
	}

	m_currentValue = n;
}

void StatBar::Render(Visualisation& v)
{
	float amountToRender = m_currentValue / m_maxValue;
	amountToRender *= 10.0f;

	v.RenderDefault(m_screenPosition, (unsigned int)amountToRender * 100, 20, m_colour);
}
