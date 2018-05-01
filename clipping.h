#ifndef CLIPPING_H
#define CLIPPING_H

#include <string>
#include <algorithm>
#include "data_structures.h"
#include "globals.h"
#include "shapes.h"

using std::min;
using std::max;

using std::string;

void line_clipping(PointH &p1, string flag);

int polygon_clipping(PointA p[], int p_size, PointA clipped_p[]);

void clip_point(PointA p, Boundary b, PointA clipped_p[], int &count, PointA first[], bool seen[], PointA last[]);

void clip_last_point(PointA clipped_p[], int &count, PointA first[], bool seen[], PointA last[]);

PointA intersect(PointA p1, PointA p2, Boundary b);

bool inside(PointA p, Boundary b);

bool cross(PointA p1, PointA p2, Boundary b);

#endif /*CLIPPING_H*/