#ifndef PIPELINES_H
#define PIPELINES_H

#include <string>
#include "data_structures.h"
#include "globals.h"
#include "plot.h"
#include "clipping.h"
#include "scan_conversion.h"

using std::string;

void point_pipeline(PointH &homogenous_point);

void line_pipeline(PointH &vertex, string flag);

int polygon_pipeline(PointA p, int end_flag);

#endif /*PIPELINES_H*/