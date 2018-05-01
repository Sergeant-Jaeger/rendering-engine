#ifndef LIGHTING_H
#define LIGHTING_H

#include <math.h>
#include "data_structures.h"
#include "globals.h"

void ambient_lighting(float color[3]);

void diffuse_lighting(float color[3]);

void specular_lighting(float color[3]);

Vector compute_reflection_vector(Vector l, Vector n);

#endif/*LIGHTING_H*/