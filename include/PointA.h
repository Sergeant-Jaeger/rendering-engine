#ifndef POINTA_H
#define POINTA_H

#include <cassert>
#include "PointH.h"

#define ATTR_CONSTANT  4
#define ATTR_R         5
#define ATTR_G         6
#define ATTR_B         7
#define ATTR_NX        8
#define ATTR_NY        9
#define ATTR_NZ       10
#define ATTR_S        11
#define ATTR_T        12
#define ATTR_WORLD_X  13
#define ATTR_WORLD_Y  14
#define ATTR_WORLD_Z  15
#define ATTR_SIZE     16

class PointH;

class PointA
{
	friend PointA operator*(const float &scalar, const PointA &multiplicand);

private:
	float x, y, z, w, c, r, g, b, nx, ny, nz, s, t, wx, wy, wz;

public:
	PointA();

	PointA(const float &new_x, const float &new_y, const float &new_z, const float &new_w,
		const float &new_c, const float&new_r, const float &new_g, const float &new_b,
		const float &new_nx, const float &new_ny, const float &new_nz, const float &new_s,
		const float &new_t, const  float &new_wx, const float &new_wy, const float &new_wz);

	PointA(const PointA &source);

	~PointA();

	PointA operator/(const float &divisor);

	PointA operator*(const float &scalar);

	PointA operator-(const PointA &subtrahend);

	PointA operator+(const PointA &addend);

	PointA& operator=(const PointA &source);

	PointA& operator=(const PointH &source);

	float& operator[](const int index);

	const float& operator[](const int index) const;

};

#endif /*POINTA_H*/