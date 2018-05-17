#ifndef EDGE_H
#define EDGE_H

#define BOUNDARY_SIZE 6

class PointA;

typedef struct Edge
{
	int yLast;

	PointA p, inc;

	Edge * next;
} Edge;

typedef enum Boundary { left, right, bottom, top, front, back } Boundary;
#endif /*EDGE_H*/