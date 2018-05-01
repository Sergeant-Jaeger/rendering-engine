#include "data_structures.h"

//Vector class defintions
Vector::Vector()
{
	for (int i = 0; i < VECTOR_SIZE; i++)
		(*this)[i] = 0;
}

Vector::Vector(const float &new_x, const float &new_y, const float &new_z)
{
	x = new_x;

	y = new_y;

	z = new_z;
}

//Vector::Vector(const Vector& source)
//{
//}

Vector::~Vector()
{
}

Vector operator*(const float &scalar, const Vector &multiplicand)
{
	Vector scalar_product;

	for (int i = 0; i < VECTOR_SIZE; i++)
		scalar_product[i] = scalar * multiplicand[i];

	return scalar_product;
}

Vector Vector::operator*(const float &scalar)
{
	Vector scalar_product;

	for (int i = 0; i < VECTOR_SIZE; i++)
		scalar_product[i] = (*this)[i] * scalar;

	return scalar_product;
}

float Vector::dot_product(const Vector &v2)
{
	return x * v2[0] + y * v2[1] + z * v2[2];
}

Vector Vector::cross_product(const Vector &v2)
{
	Vector cross_product_vector;

	cross_product_vector[0] = (y * v2[2]) - (z * v2[1]);

	cross_product_vector[1] = -((x * v2[2]) - (z * v2[0]));

	cross_product_vector[2] = (x * v2[1]) - (y * v2[0]);

	return cross_product_vector;
}

float Vector::magnitude_squared()
{
	return pow(x, 2) + pow(y, 2) + pow(z, 2);
}

void Vector::normalize()
{
	float magnitude = sqrt(this->magnitude_squared());

	for (int i = 0; i < VECTOR_SIZE; i++)
		(*this)[i] = (*this)[i] / magnitude;
}

Vector Vector::operator+(const Vector &addend)
{
	Vector sum;

	for (int i = 0; i < VECTOR_SIZE; i++)
		sum[i] = (*this)[i] + addend[i];

	return sum;
}

Vector Vector::operator-(const Vector &subtrahend)
{
	Vector difference;

	for (int i = 0; i < VECTOR_SIZE; i++)
		difference[i] = (*this)[i] - subtrahend[i];

	return difference;
}

Vector& Vector::operator=(const Vector &source)
{
	if (this != &source)
		for (int i = 0; i < VECTOR_SIZE; i++)
			(*this)[i] = source[i];

	return *this;
}

float& Vector::operator[](const int index)
{
	assert(index >= 0 && index < VECTOR_SIZE);

	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	else
		return z;
}

const float& Vector::operator[](const int index) const
{
	assert(index >= 0 && index < VECTOR_SIZE);

	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	else
		return z;
}

//change to operator overload?
//PointH Vector::convert()
//{
//	PointH convert_pointh;
//
//	for (int i = 0; i < VECTOR_SIZE; i++)
//		convert_pointh[i] = (*this)[i];
//
//	return convert_pointh;
//}
//end Vector class definitions

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

Vector Point::operator-(const Point &subtrahend) const
{
	Vector difference_vector;

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

//change to operator overload?
//PointH Point::convert()
//{
//	PointH convert_pointh;
//
//	for (int i = 0; i < POINT_SIZE; i++)
//		convert_pointh[i] = (*this)[i];
//
//	return convert_pointh;
//}
//end Point class definitions

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

PointH& PointH::operator=(const Vector &source)
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

//XForm class definitions
XForm::XForm()
{
	radians = M_PI / 180;

	this->default_matrix();	
}

XForm::XForm(const XForm& source)
{
	radians = M_PI / 180;

	this->default_matrix();

	this->copy_matrix(source);
}

XForm::~XForm()
{
}

void XForm::default_matrix()
{
	for (int i = 0; i < XFORM_SIZE; i++)
		for (int j = 0; j < XFORM_SIZE; j++)
			matrix[i][j] = 0;
}

void XForm::copy_matrix(const XForm &source)
{
	for (int i = 0; i < XFORM_SIZE; i++)
		for (int j = 0; j < XFORM_SIZE; j++)
			matrix[i][j] = source.matrix[i][j];
}

void XForm::identity_matrix()
{
	for (int i = 0; i < XFORM_SIZE; i++)
		for (int j = 0; j < XFORM_SIZE; j++)
			if (i == j)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
}

void XForm::translate_matrix(const double &tx, const double &ty, const double &tz)
{
	this->identity_matrix();

	matrix[0][3] = tx;

	matrix[1][3] = ty;

	matrix[2][3] = tz;
}

void XForm::scale_matrix(const double &sx, const double &sy, const double &sz)
{
	this->identity_matrix();

	matrix[0][0] = sx;

	matrix[1][1] = sy;

	matrix[2][2] = sz;
}

void XForm::rotate_xy_matrix(const double &theta)
{
	this->identity_matrix();

	matrix[0][0] = cos(theta * radians);

	matrix[0][1] = -sin(theta * radians);

	matrix[1][0] = sin(theta * radians);

	matrix[1][1] = cos(theta * radians);
}

void XForm::rotate_yz_matrix(const double &theta)
{
	this->identity_matrix();

	matrix[1][1] = cos(theta * radians);

	matrix[1][2] = -sin(theta * radians);

	matrix[2][1] = sin(theta * radians);

	matrix[2][2] = cos(theta * radians);
}

void XForm::rotate_zx_matrix(const double &theta)
{
	this->identity_matrix();

	matrix[0][0] = cos(theta * radians);

	matrix[0][2] = sin(theta * radians);

	matrix[2][0] = -sin(theta * radians);

	matrix[2][2] = cos(theta * radians);
}

void XForm::inv_translate_matrix(const double &tx, const double &ty, const double &tz)
{
	this->identity_matrix();

	matrix[0][3] = -tx;

	matrix[1][3] = -ty;

	matrix[2][3] = -tz;
}

void XForm::inv_scale_matrix(const double &sx, const double &sy, const double &sz)
{
	this->identity_matrix();

	matrix[0][0] = 1 / sx;

	matrix[1][1] = 1 / sy;

	matrix[2][2] = 1 / sz;
}

void XForm::inv_rotate_xy_matrix(const double &theta)
{
	this->identity_matrix();

	matrix[0][0] = cos(theta * radians);

	matrix[0][1] = sin(theta * radians);

	matrix[1][0] = -sin(theta * radians);

	matrix[1][1] = cos(theta * radians);
}

void XForm::inv_rotate_yz_matrix(const double &theta)
{
	this->identity_matrix();

	matrix[1][1] = cos(theta * radians);

	matrix[1][2] = sin(theta * radians);

	matrix[2][1] = -sin(theta * radians);

	matrix[2][2] = cos(theta * radians);
}

void XForm::inv_rotate_zx_matrix(const double &theta)
{
	this->identity_matrix();

	matrix[0][0] = cos(theta * radians);

	matrix[0][2] = -sin(theta * radians);

	matrix[2][0] = sin(theta * radians);

	matrix[2][2] = cos(theta * radians);
}

void XForm::transpose_matrix()
{
	float temp;

	for(int i = 0; i < XFORM_SIZE; i++)
		for (int j = 0; j < XFORM_SIZE; j++)
		{
			if (i > j)
			{
				temp = matrix[i][j];
				matrix[i][j] = matrix[j][i];
				matrix[j][i] = temp;
			}
		}
}

void XForm::eye_matrix(const Point &eye)
{
	this->identity_matrix();

	for (int i = 0; i < 3; i++)
		matrix[i][3] = -eye[i];
}

void XForm::vua_matrix(const Vector &v, const Vector &u, const Vector &a)
{
	this->identity_matrix();

	for (int i = 0; i < 3; i++)
	{
		matrix[0][i] = v[i];

		matrix[1][i] = u[i];

		matrix[2][i] = a[i];
	}
}

void XForm::camera_matrix(const double &theta, const double &n, const double &f, const double &a)
{
	matrix[0][0] = 1 / (2 * a * tan((theta / 2) * radians));
	matrix[0][2] = .5;
	matrix[1][1] = 1 / (2 * tan((theta / 2) * radians));
	matrix[1][2] = .5;
	matrix[2][2] = f / (f - n);
	matrix[2][3] = -(f * n) / (f - n);
	matrix[3][2] = 1;
}

void XForm::clip_matrix(const int &width, const int &height)
{
	this->identity_matrix();

	matrix[0][0] = width - 0.001;
	matrix[0][3] = -0.5;
	matrix[1][1] = -(height - 0.001);
	matrix[1][3] = (height - 0.001) - 0.5;
}

XForm XForm::operator*(const XForm &multiplicand)
{
	XForm product_xform;

	for (int i = 0; i < XFORM_SIZE; i++)
		for (int j = 0; j < XFORM_SIZE; j++)
			for (int k = 0; k < XFORM_SIZE; k++)
				product_xform.matrix[i][j] = product_xform.matrix[i][j] + (matrix[i][k] * multiplicand.matrix[k][j]);

	return product_xform;
}

PointH XForm::operator*(const PointH &multiplicand)
{
	PointH product_pointh(0, 0, 0, 0);

	for (int i = 0; i < XFORM_SIZE; i++)
		for (int j = 0; j < XFORM_SIZE; j++)
			product_pointh[i] = product_pointh[i] + matrix[i][j] * multiplicand[j];

	return product_pointh;
}

XForm& XForm::operator=(const XForm &source)
{
	if (this != &source)
	{
		this->~XForm();

		radians = M_PI / 180;

		this->default_matrix();

		this->copy_matrix(source);
	}

	return *this;
}
//end XForm class definitions

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

LightA::LightA()
{
	r = 0.0;
	g = 0.0;
	b = 0.0;
}

LightA::LightA(float nr, float ng, float nb)
{
	r = nr;
	g = ng;
	b = nb;
}

LightA::LightA(const float color[], float intensity)
{
	r = color[0] * intensity;
	g = color[1] * intensity;
	b = color[2] * intensity;
}

//LightA::LightA(LightA &source)
//{
//}

LightA::~LightA()
{

}

float& LightA::operator[](const int index)
{
	assert(index >= 0 && index < LIGHTA_SIZE);

	if (index == 0)
		return this->r;
	else if (index == 1)
		return this->g;
	else
		return this->b;
}

const float& LightA::operator[](const int index) const
{
	assert(index >= 0 && index < LIGHTA_SIZE);

	if (index == 0)
		return this->r;
	else if (index == 1)
		return this->g;
	else
		return this->b;
}


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