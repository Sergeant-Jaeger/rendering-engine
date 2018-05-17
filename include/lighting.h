#ifndef LIGHTING_H
#define LIGHTING_H

#include <math.h>
#include "Point.h"
#include "PointH.h"
#include "PointA.h"
#include "Vector3.h"
#include "XForm.h"
#include "LightA.h"
#include "LightP.h"
#include "LightF.h"
#include "Edge.h"
#include "Globals.h"

void ambient_lighting(float color[3]);

void diffuse_lighting(float color[3]);

void specular_lighting(float color[3]);

Vector3 compute_reflection_vector(Vector3 l, Vector3 n);

#endif/*LIGHTING_H*/