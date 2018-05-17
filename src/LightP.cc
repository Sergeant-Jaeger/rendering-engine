#include "LightP.h"

LightP::LightP()
{
	r = 0;
	g = 0;
	b = 0;
}

LightP::LightP(const float pos[3], const float color[], float intensity)
{
	for (int i = 0; i < 3; i++)
		position[i] = pos[i];

	r = color[0] * intensity;
	g = color[1] * intensity;
	b = color[2] * intensity;
}

//LightP::LightP(LightP &source)
//{
//
//}

LightP::~LightP()
{

}

float& LightP::operator[](const int index)
{
	assert(index >= 0 && index < LIGHTP_SIZE);

	if (index == 0)
		return this->position[0];
	else if (index == 1)
		return this->position[1];
	else if (index == 2)
		return this->position[2];
	else if (index == 3)
		return this->r;
	else if (index == 4)
		return this->g;
	else
		return this->b;
}

const float& LightP::operator[](const int index) const
{
	assert(index >= 0 && index < LIGHTP_SIZE);

	if (index == 0)
		return this->position[0];
	else if (index == 1)
		return this->position[1];
	else if (index == 2)
		return this->position[2];
	else if (index == 3)
		return this->r;
	else if (index == 4)
		return this->g;
	else
		return this->b;
}