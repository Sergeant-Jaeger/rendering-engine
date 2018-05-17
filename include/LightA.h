#ifndef LIGHTA_H
#define LIGHTA_H

#include <cassert>

#define LIGHTA_SIZE 3

class LightA
{
private:
	float r = 0, g = 0, b = 0;

public:
	LightA();
	LightA(const float color[], float intensity);
	LightA(float nr, float ng, float nb);
	~LightA();

	float& operator[](const int index);

	const float& operator[](const int index) const;
};
#endif /*LIGHTA_H*/