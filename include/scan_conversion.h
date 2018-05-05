#ifndef SCAN_CONVERSION_H
#define SCAN_CONVERSION_H

#include "data_structures.h"
#include "globals.h"
#include "plot.h"

void scan_convert(PointA p[], int p_size);

bool build_edge_list(PointA p[], int p_size);

void make_edge_rec(PointA upper, PointA lower);

void add_active_list(int scanline, Edge * &AET);

void insert_edge(Edge * &linked_list, Edge * e);

void update_AET(int scanline, Edge * &AET);

void delete_after(Edge * q);

void resort_AET(Edge * &AET);

void fill_between_edges(int scanline, Edge * AET);

#endif /*SCAN_CONVERSION_H*/