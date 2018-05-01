#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#define _USE_MATH_DEFINES

#define VECTOR_SIZE    3

#define POINT_SIZE     3

#define POINTH_SIZE    4

#define XFORM_SIZE     4

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

#define BOUNDARY_SIZE  6

#define LIGHTA_SIZE    3

#define LIGHTF_SIZE    6

#define LIGHTP_SIZE    6

#include <math.h>
#include <cassert>

class Vector;
class Point;
class PointH;
class XForm;
class PointA;
class LightA;
class LightF;
class LightP;

class Vector
{
	friend Vector operator*(const float &scalar, const Vector &multiplicand);

private:
	float x, y, z;

public:
	Vector();

	Vector(const float &new_x, const float &new_y, const float &new_z);

	//Vector(const Vector &source);

	~Vector();

	Vector operator*(const float &scalar);

	float dot_product(const Vector &v2);

	Vector cross_product(const Vector &v2);

	float magnitude_squared();

	void normalize();

	Vector operator+(const Vector &addend);

	Vector operator-(const Vector &subtrahend);

	Vector& operator=(const Vector &source);

	float& operator[](const int index);

	const float& operator[](const int index) const;

	//PointH convert();
};

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

	Vector operator-(const Point &subtrahend) const;

	Point& operator=(const Point &source);

	float& operator[](const int index);

	const float& operator[](const int index) const;

	//PointH convert();
};

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

	PointH& operator=(const Vector &source);

	PointH& operator=(const Point &source);

	PointH& operator=(const PointA &source);

	float& operator[](const int index);

	const float& operator[](const int index) const;
};

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

	void vua_matrix(const Vector &v, const Vector &u, const Vector &a);

	void camera_matrix(const double &theta, const double &n, const double &f, const double &a);

	void clip_matrix(const int &width, const int &height);

	XForm operator*(const XForm &multiplicand);

	PointH operator*(const PointH &multiplicand);

	XForm& operator=(const XForm &source);
};

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

class LightA
{
private:
	float r = 0, g = 0, b = 0;

public:
	LightA();
	LightA(const float color[], float intensity);
	LightA(float nr, float ng, float nb);
	//LightA(LightA &source);
	~LightA();

	float& operator[](const int index);

	const float& operator[](const int index) const;
};

class LightF
{
private:
	Vector direction;
	float r, g, b;

public:
	LightF();
	LightF(const float dir[3], const float color[], float intensity);
	//LightF(const LightF &source);
	~LightF();

	float& operator[](const int index);

	const float& operator[](const int index) const;
};

class LightP
{
private:
	Point position;
	float r, g, b;
public:
	LightP();
	LightP(const float pos[3], const float color[], float intensity);
	//LightP(LightP &source);
	~LightP();

	float& operator[](const int index);

	const float& operator[](const int index) const;
};

typedef struct Edge
{
	int yLast;
	
	PointA p, inc;
	
	Edge * next;
} Edge;

typedef enum Boundary {left, right, bottom, top, front, back} Boundary;


#endif /*DATA_STRUCTURES_H*/