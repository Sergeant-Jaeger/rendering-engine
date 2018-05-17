#ifndef VECTOR3_H
#define VECTOR3_H

#include <cassert>
#include <math.h>

#define VECTOR_SIZE 3

class Vector3
{
	friend Vector3 operator*(const float &scalar, const Vector3 &multiplicand);

private:
	float x, y, z;

public:
	Vector3();

	Vector3(const float &new_x, const float &new_y, const float &new_z);

	~Vector3();

	Vector3 operator*(const float &scalar);

	float dot_product(const Vector3 &v2);

	Vector3 cross_product(const Vector3 &v2);

	float magnitude_squared();

	void normalize();

	Vector3 operator+(const Vector3 &addend);

	Vector3 operator-(const Vector3 &subtrahend);

	Vector3& operator=(const Vector3 &source);

	float& operator[](const int index);

	const float& operator[](const int index) const;
};
#endif /*VECTOR3_H*/