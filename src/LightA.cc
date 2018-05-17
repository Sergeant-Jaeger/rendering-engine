#include "LightA.h"

LightA::LightA()
{
	r = 0.0;
	g = 0.0;
	b = 0.0;
}

LightA::LightA(float nr, float ng, float nb)
{
	r = nr;
	g = ng;
	b = nb;
}

LightA::LightA(const float color[], float intensity)
{
	r = color[0] * intensity;
	g = color[1] * intensity;
	b = color[2] * intensity;
}

//LightA::LightA(LightA &source)
//{
//}

LightA::~LightA()
{

}

float& LightA::operator[](const int index)
{
	assert(index >= 0 && index < LIGHTA_SIZE);

	if (index == 0)
		return this->r;
	else if (index == 1)
		return this->g;
	else
		return this->b;
}

const float& LightA::operator[](const int index) const
{
	assert(index >= 0 && index < LIGHTA_SIZE);

	if (index == 0)
		return this->r;
	else if (index == 1)
		return this->g;
	else
		return this->b;
}