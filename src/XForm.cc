#include "XForm.h"

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

	for (int i = 0; i < XFORM_SIZE; i++)
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

void XForm::vua_matrix(const Vector3 &v, const Vector3 &u, const Vector3 &a)
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