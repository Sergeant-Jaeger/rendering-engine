#ifndef PLOT_H
#define PLOT_H

#include "rd_direct.h"
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

void pixel_plot(PointH &plot_pointh);

void poly_plot(PointH &plot_pointh, float color[3]);

#endif /*PLOT_H*/