#ifndef XFORM_H
#define XFORM_H

#include <cassert>
#include <math.h>
#include "Point.h"
#include "PointH.h"
#include "Vector3.h"

#define _USE_MATH_DEFINES
#define XFORM_SIZE 4

class Point;
class PointH;
class Vector3;

class XForm
{
private:
	float radians;

public:
	XForm();

	XForm(const XForm &source);

	~XForm();

	float matrix[XFORM_SIZE][XFORM_SIZE];

	void default_matrix();

	void copy_matrix(const XForm &source);

	void identity_matrix();

	void translate_matrix(const double &tx, const double &ty, const double &tz);

	void scale_matrix(const double &sx, const double &sy, const double &sz);

	void rotate_xy_matrix(const double &theta);

	void rotate_yz_matrix(const double &theta);

	void rotate_zx_matrix(const double &theta);

	void inv_translate_matrix(const double &tx, const double &ty, const double &tz);

	void inv_scale_matrix(const double &sx, const double &sy, const double &sz);

	void inv_rotate_xy_matrix(const double &theta);

	void inv_rotate_yz_matrix(const double &theta);

	void inv_rotate_zx_matrix(const double &theta);

	void transpose_matrix();

	void eye_matrix(const Point &eye);

	void vua_matrix(const Vector3 &v, const Vector3 &u, const Vector3 &a);

	void camera_matrix(const double &theta, const double &n, const double &f, const double &a);

	void clip_matrix(const int &width, const int &height);

	XForm operator*(const XForm &multiplicand);

	PointH operator*(const PointH &multiplicand);

	XForm& operator=(const XForm &source);
};
#endif /*XFORM_H*/