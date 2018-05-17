#ifndef LIGHTF_H
#define LIGHTF_H

#include <cassert>
#include "Vector3.h"

#define LIGHTF_SIZE 6

class Vector3;

class LightF
{
private:
	Vector3 direction;
	float r, g, b;

public:
	LightF();
	LightF(const float dir[3], const float color[], float intensity);
	~LightF();

	float& operator[](const int index);

	const float& operator[](const int index) const;
};
#endif /*LIGHTF_H*/