#include "LightF.h"

LightF::LightF()
{
	r = 0;
	g = 0;
	b = 0;
}

LightF::LightF(const float dir[3], const float color[], float intensity)
{
	for (int i = 0; i < 3; i++)
		direction[i] = dir[i];

	r = color[0] * intensity;
	g = color[1] * intensity;
	b = color[2] * intensity;
}

//LightF::LightF(const LightF &source)
//{
//	
//}

LightF::~LightF()
{

}

float& LightF::operator[](const int index)
{
	assert(index >= 0 && index < LIGHTF_SIZE);

	if (index == 0)
		return this->direction[0];
	else if (index == 1)
		return this->direction[1];
	else if (index == 2)
		return this->direction[2];
	else if (index == 3)
		return this->r;
	else if (index == 4)
		return this->g;
	else
		return this->b;
}

const float& LightF::operator[](const int index) const
{
	assert(index >= 0 && index < LIGHTF_SIZE);

	if (index == 0)
		return this->direction[0];
	else if (index == 1)
		return this->direction[1];
	else if (index == 2)
		return this->direction[2];
	else if (index == 3)
		return this->r;
	else if (index == 4)
		return this->g;
	else
		return this->b;
}