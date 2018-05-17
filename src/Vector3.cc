#include "Vector3.h"

//Vector3 class defintions
Vector3::Vector3()
{
	for (int i = 0; i < VECTOR_SIZE; i++)
		(*this)[i] = 0;
}

Vector3::Vector3(const float &new_x, const float &new_y, const float &new_z)
{
	x = new_x;

	y = new_y;

	z = new_z;
}

//Vector3::Vector3(const Vector3& source)
//{
//}

Vector3::~Vector3()
{
}

Vector3 operator*(const float &scalar, const Vector3 &multiplicand)
{
	Vector3 scalar_product;

	for (int i = 0; i < VECTOR_SIZE; i++)
		scalar_product[i] = scalar * multiplicand[i];

	return scalar_product;
}

Vector3 Vector3::operator*(const float &scalar)
{
	Vector3 scalar_product;

	for (int i = 0; i < VECTOR_SIZE; i++)
		scalar_product[i] = (*this)[i] * scalar;

	return scalar_product;
}

float Vector3::dot_product(const Vector3 &v2)
{
	return x * v2[0] + y * v2[1] + z * v2[2];
}

Vector3 Vector3::cross_product(const Vector3 &v2)
{
	Vector3 cross_product_vector;

	cross_product_vector[0] = (y * v2[2]) - (z * v2[1]);

	cross_product_vector[1] = -((x * v2[2]) - (z * v2[0]));

	cross_product_vector[2] = (x * v2[1]) - (y * v2[0]);

	return cross_product_vector;
}

float Vector3::magnitude_squared()
{
	return pow(x, 2) + pow(y, 2) + pow(z, 2);
}

void Vector3::normalize()
{
	float magnitude = sqrt(this->magnitude_squared());

	for (int i = 0; i < VECTOR_SIZE; i++)
		(*this)[i] = (*this)[i] / magnitude;
}

Vector3 Vector3::operator+(const Vector3 &addend)
{
	Vector3 sum;

	for (int i = 0; i < VECTOR_SIZE; i++)
		sum[i] = (*this)[i] + addend[i];

	return sum;
}

Vector3 Vector3::operator-(const Vector3 &subtrahend)
{
	Vector3 difference;

	for (int i = 0; i < VECTOR_SIZE; i++)
		difference[i] = (*this)[i] - subtrahend[i];

	return difference;
}

Vector3& Vector3::operator=(const Vector3 &source)
{
	if (this != &source)
		for (int i = 0; i < VECTOR_SIZE; i++)
			(*this)[i] = source[i];

	return *this;
}

float& Vector3::operator[](const int index)
{
	assert(index >= 0 && index < VECTOR_SIZE);

	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	else
		return z;
}

const float& Vector3::operator[](const int index) const
{
	assert(index >= 0 && index < VECTOR_SIZE);

	if (index == 0)
		return x;
	else if (index == 1)
		return y;
	else
		return z;
}
//end Vector3 class definitions