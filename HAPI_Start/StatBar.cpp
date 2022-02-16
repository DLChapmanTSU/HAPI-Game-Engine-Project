#include "StatBar.h"
#include "Visualisation.h"

StatBar::StatBar(Vector3& p, unsigned int m, HAPISPACE::HAPI_TColour& c)
{
	m_screenPosition = p;
	m_maxValue = m;
	m_currentValue = m;
	m_colour = c;
}

//Sets the value of the slider, which determines how long the slider should be when rendered
void StatBar::SetValue(unsigned int n)
{
	if (n > m_maxValue) {
		n = m_maxValue;
	}

	m_currentValue = n;
}

//Render a default shape with a length based on the value of the slider
void StatBar::Render(Visualisation& v)
{
	float amountToRender = (float)m_currentValue / (float)m_maxValue;
	amountToRender *= 10;

	v.RenderDefault(m_screenPosition, (unsigned int)amountToRender * 100, 20, m_colour);
}
