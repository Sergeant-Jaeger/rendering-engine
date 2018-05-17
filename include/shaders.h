#ifndef SHADERS_H
#define SHADERS_H

#include "Globals.h"

void matte(float color[3]);

void metal(float color[3]);

void plastic(float color[3]);

float clamp_float(float a, float x, float b);

#endif /*SHADERS_H*/