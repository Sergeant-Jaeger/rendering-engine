#ifndef LIGHTP_H
#define LIGHTP_H

#include <cassert>
#include "Point.h"

#define LIGHTP_SIZE 6

class Point;

class LightP
{
private:
	Point position;
	float r, g, b;
public:
	LightP();
	LightP(const float pos[3], const float color[], float intensity);
	~LightP();

	float& operator[](const int index);

	const float& operator[](const int index) const;
};
#endif /*LIGHTP_H*/