#ifndef POINT_H
#define POINT_H

#include <cassert>
#include "Vector3.h"

#define POINT_SIZE 3

class Vector3;

class Point
{
	friend Point operator*(const float &scalar, const Point &multiplicand);

private:
	float x, y, z;

public:
	Point();

	Point(const float &new_x, const float &new_y, const float &new_z);

	Point(const Point &source);

	~Point();

	Point operator*(const float &scalar);

	Vector3 operator-(const Point &subtrahend) const;

	Point& operator=(const Point &source);

	float& operator[](const int index);

	const float& operator[](const int index) const;
};
#endif /*POINT_H*/