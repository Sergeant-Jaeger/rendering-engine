#include "Point.h"

//Point class definitions
Point::Point()
{
	for (int i = 0; i < POINT_SIZE; i++)
		(*this)[i] = 0;
}

Point::Point(const float &new_x, const float &new_y, const float &new_z)
{
	x = new_x;

	y = new_y;

	z = new_z;
}

Point::Point(const Point& source)
{
	for (int i = 0; i < POINT_SIZE; i++)
		(*this)[i] = source[i];
}

Point::~Point()
{
}

Point operator*(const float &scalar, const Point &multiplicand)
{
	Point scalar_product;

	for (int i = 0; i < POINT_SIZE; i++)
		scalar_product[i] = scalar * multiplicand[i];

	return scalar_product;
}

Point Point::operator*(const float &scalar)
{
	Point scalar_product;

	for (int i = 0; i < POINT_SIZE; i++)
		scalar_product[i] = (*this)[i] * scalar;

	return scalar_product;
}

Vector3 Point::operator-(const Point &subtrahend) const
{
	Vector3 difference_vector;

	for (int i = 0; i < VECTOR_SIZE; i++)
		difference_vector[i] = (*this)[i] - subtrahend[i];

	return difference_vector;
}

Point& Point::operator=(const Point &source)
{
	if (this != &source)
		for (int i = 0; i < POINT_SIZE; i++)
			(*this)[i] = source[i];

	return *this;
}

float& Point::operator[](const int index)
{
	assert(index >= 0 && index < POINT_SIZE);

	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	else
		return z;
}

const float& Point::operator[](const int index) const
{
	assert(index >= 0 && index < POINT_SIZE);

	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	else
		return z;
}
//end Point class definitions