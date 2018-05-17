#ifndef POINTH_H
#define POINTH_H

#include <cassert>
#include "Vector3.h"
#include "Point.h"
#include "PointA.h"

#define POINTH_SIZE 4

class Vector3;
class Point;
class PointA;

class PointH
{
private:
	float x, y, z, w;

public:
	PointH();

	PointH(const float &new_x, const float &new_y, const float &new_z, const float &new_w);

	PointH(const PointH &source);

	~PointH();

	PointH& operator=(const PointH &source);

	PointH& operator=(const Vector3 &source);

	PointH& operator=(const Point &source);

	PointH& operator=(const PointA &source);

	float& operator[](const int index);

	const float& operator[](const int index) const;
};
#endif /*POINTH_H*/