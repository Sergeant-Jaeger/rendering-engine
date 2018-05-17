#ifndef PIPELINES_H
#define PIPELINES_H

#include <string>
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
#include "Plot.h"
#include "Clipping.h"
#include "ScanConversion.h"

using std::string;

void point_pipeline(PointH &homogenous_point);

void line_pipeline(PointH &vertex, string flag);

int polygon_pipeline(PointA p, int end_flag);

#endif /*PIPELINES_H*/