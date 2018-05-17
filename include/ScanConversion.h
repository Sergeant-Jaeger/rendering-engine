#ifndef SCANCONVERSION_H
#define SCANCONVERSION_H

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

void scan_convert(PointA p[], int p_size);

bool build_edge_list(PointA p[], int p_size);

void make_edge_rec(PointA upper, PointA lower);

void add_active_list(int scanline, Edge * &AET);

void insert_edge(Edge * &linked_list, Edge * e);

void update_AET(int scanline, Edge * &AET);

void delete_after(Edge * q);

void resort_AET(Edge * &AET);

void fill_between_edges(int scanline, Edge * AET);

#endif /*SCANCONVERSION_H*/