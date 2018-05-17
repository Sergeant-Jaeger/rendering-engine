#include "Shaders.h"
#include "Lighting.h"

void matte(float color[3])
{
	float matte_ambient[3]{ 0, 0, 0 };

	float matte_diffuse[3]{ 0, 0, 0 };

	ambient_lighting(matte_ambient);

	diffuse_lighting(matte_diffuse);
	
	for (int i = 0; i < 3; i++)
	{
		matte_diffuse[i] = clamp_float(0, diffuse_k * surface_color[i] * matte_diffuse[i], 1);

		color[i] = clamp_float(0, matte_ambient[i] + matte_diffuse[i], 1);
	}
}

void metal(float color[3])
{
	float metal_ambient[3]{ 0, 0, 0 };

	float metal_specular[3]{ 0, 0, 0 };

	ambient_lighting(metal_ambient);

	specular_lighting(metal_specular);

	for (int i = 0; i < 3; i++)
	{
		metal_specular[i] = clamp_float(0, (specular_k * surface_color[i] * metal_specular[i]), 1);

		color[i] = clamp_float(0, metal_ambient[i] + metal_specular[i], 1);
	}
}

void plastic(float color[3])
{
	float plastic_ambient[3]{ 0, 0, 0 };

	float plastic_diffuse[3]{ 0, 0, 0 };

	float plastic_specular[3]{ 0, 0, 0 };

	ambient_lighting(plastic_ambient);

	diffuse_lighting(plastic_diffuse);

	specular_lighting(plastic_specular);

	for (int i = 0; i < 3; i++)
	{
		plastic_diffuse[i] = (diffuse_k * surface_color[i] * plastic_diffuse[i]);
		
		plastic_specular[i] = (specular_k * specular_color[i] * plastic_specular[i]);

		color[i] = clamp_float(0, plastic_ambient[i] + plastic_diffuse[i] + plastic_specular[i], 1);
	}
}

float clamp_float(float a, float x, float b)
{
	float result;

	if (x < a)
		result = a;
	else if (x > b)
		result = b;
	else
		result = x;

	return result;
		
}