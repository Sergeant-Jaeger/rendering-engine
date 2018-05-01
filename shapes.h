#ifndef SHAPES_H
#define SHAPES_H

#include <math.h>
#include <vector>
#include "rd_direct.h"
#include "data_structures.h"
#include "pipelines.h"
#include "globals.h"
#include "plot.h"

using std::vector;

void point_set(int nvertex, const float * vertex);

//void bresenham_line(const float start[], const float end[]);

void digital_differential_analyzer(PointH &start, PointH &end);

void midpoint_circle(const float center[3], const float radius);

void polygon_set(const float * vertex, int nface, const int * face);

void cube();

void sphere(float radius, float zmin, float zmax, float thetamax);

void cone(float height, float radius, float thetamax);

void cylinder(float radius, float zmin, float zmax, float thetamax);

void disk(float height, float radius, float theta);

#endif /*SHAPES_H*/