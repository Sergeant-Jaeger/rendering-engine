#include "PointA.h"

//PointA class definitions
PointA::PointA()
{
	for (int i = 0; i < ATTR_SIZE; i++)
		(*this)[i] = 0;
}

PointA::PointA(const float &new_x, const float &new_y, const float &new_z, const float &new_w,
	const float &new_c, const float&new_r, const float &new_g, const float &new_b,
	const float &new_nx, const float &new_ny, const float &new_nz, const float &new_s,
	const float &new_t, const  float &new_wx, const float &new_wy, const float &new_wz)
{
	x = new_x;
	y = new_y;
	z = new_z;
	w = new_w;
	c = new_c;
	r = new_r;
	g = new_g;
	b = new_b;
	nx = new_nx;
	ny = new_ny;
	nz = new_nz;
	s = new_s;
	t = new_t;
	wx = new_wx;
	wy = new_wy;
	wz = new_wz;
}

PointA::PointA(const PointA &source)
{
	for (int i = 0; i < ATTR_SIZE; i++)
		(*this)[i] = source[i];
}

PointA::~PointA()
{

}

PointA operator*(const float &scalar, const PointA &multiplicand)
{
	PointA scalar_product;

	for (int i = 0; i < ATTR_SIZE; i++)
		scalar_product[i] = scalar * multiplicand[i];

	return scalar_product;
}

PointA PointA::operator/(const float &divisor)
{
	PointA quotient;

	for (int i = 0; i < ATTR_SIZE; i++)
		quotient[i] = (*this)[i] / divisor;

	return quotient;
}

PointA PointA::operator*(const float &scalar)
{
	PointA scalar_product;

	for (int i = 0; i < ATTR_SIZE; i++)
		scalar_product[i] = (*this)[i] * scalar;

	return scalar_product;
}

PointA PointA::operator-(const PointA &subtrahend)
{
	PointA difference;

	for (int i = 0; i < ATTR_SIZE; i++)
		difference[i] = (*this)[i] - subtrahend[i];

	return difference;
}

PointA PointA::operator+(const PointA &addend)
{
	PointA sum;

	for (int i = 0; i < ATTR_SIZE; i++)
		sum[i] = (*this)[i] + addend[i];

	return sum;
}

PointA& PointA::operator=(const PointA &source)
{
	if (this != &source)
		for (int i = 0; i < ATTR_SIZE; i++)
			(*this)[i] = source[i];

	return *this;
}

PointA& PointA::operator=(const PointH &source)
{
	for (int i = 0; i < POINTH_SIZE; i++)
		(*this)[i] = source[i];

	return *this;
}

float& PointA::operator[](const int index)
{
	assert(index >= 0 && index < ATTR_SIZE);

	if (index == 0)
		return this->x;
	else if (index == 1)
		return this->y;
	else if (index == 2)
		return this->z;
	else if (index == 3)
		return this->w;
	else if (index == 4)
		return this->c;
	else if (index == 5)
		return this->r;
	else if (index == 6)
		return this->g;
	else if (index == 7)
		return this->b;
	else if (index == 8)
		return this->nx;
	else if (index == 9)
		return this->ny;
	else if (index == 10)
		return this->nz;
	else if (index == 11)
		return this->s;
	else if (index == 12)
		return this->t;
	else if (index == 13)
		return this->wx;
	else if (index == 14)
		return this->wy;
	else
		return this->wz;
}

const float& PointA::operator[](const int index) const
{
	assert(index >= 0 && index < ATTR_SIZE);

	if (index == 0)
		return this->x;
	else if (index == 1)
		return this->y;
	else if (index == 2)
		return this->z;
	else if (index == 3)
		return this->w;
	else if (index == 4)
		return this->c;
	else if (index == 5)
		return this->r;
	else if (index == 6)
		return this->g;
	else if (index == 7)
		return this->b;
	else if (index == 8)
		return this->nx;
	else if (index == 9)
		return this->ny;
	else if (index == 10)
		return this->nz;
	else if (index == 11)
		return this->s;
	else if (index == 12)
		return this->t;
	else if (index == 13)
		return this->wx;
	else if (index == 14)
		return this->wy;
	else
		return this->wz;
}
//end PointA class definitions