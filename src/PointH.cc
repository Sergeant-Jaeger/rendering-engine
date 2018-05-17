#include "PointH.h"

//PointH class definitions
PointH::PointH()
{
	for (int i = 0; i < POINTH_SIZE; i++)
		if (i != 3)
			(*this)[i] = 0;
		else
			(*this)[i] = 1;
}

PointH::PointH(const float &new_x, const float &new_y, const float &new_z, const float &new_w)
{
	x = new_x;

	y = new_y;

	z = new_z;

	w = new_w;
}

PointH::PointH(const PointH &source)
{
}

PointH::~PointH()
{
}

PointH& PointH::operator=(const PointH &source)
{
	if (this != &source)
		for (int i = 0; i < POINTH_SIZE; i++)
			(*this)[i] = source[i];

	return *this;
}

PointH& PointH::operator=(const Vector3 &source)
{
	for (int i = 0; i < VECTOR_SIZE; i++)
		(*this)[i] = source[i];

	return *this;
}

PointH& PointH::operator=(const Point &source)
{
	for (int i = 0; i < POINT_SIZE; i++)
		(*this)[i] = source[i];

	return *this;
}

PointH& PointH::operator=(const PointA &source)
{
	for (int i = 0; i < POINTH_SIZE; i++)
		(*this)[i] = source[i];

	return *this;
}

float& PointH::operator[](const int index)
{
	assert(index >= 0 && index < POINTH_SIZE);

	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	else if (index == 2)
		return z;
	else
		return w;
}

const float& PointH::operator[](const int index) const
{
	assert(index >= 0 && index < POINTH_SIZE);

	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	else if (index == 2)
		return z;
	else
		return w;
}
//end PointH class definitions
