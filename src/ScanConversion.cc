#include "ScanConversion.h"

Edge* AET;

void scan_convert(PointA p[], int p_size)
{
	//AET = edgetable[0];

	if (!build_edge_list(p, p_size))
		return;

	//AET = 0;

	//loop an integer, scan over the lines of the display
	for (int i = 0; i < display_ySize; i++)
	{
		//take the edges starting on this scanline from the edge table and add them to the active edge table(AET)
		add_active_list(i, AET);

		if (AET != 0)
		{
			//fill between the edge pairs in the AET
			fill_between_edges(i, AET);

			//update the AET
			update_AET(i, AET);

			//resort the AET
			resort_AET(AET);
		}

	}
}

bool build_edge_list(PointA p[], int p_size)
{
	bool scanline_crossed = false;

	int v1, v2;

	v1 = p_size - 1;

	//loop v2 over the number of vertices in the polygon
	for (v2 = 0; v2 < p_size; v2++)
	{
		if (ceil(p[v1][1]) != ceil(p[v2][1]))
		{
			scanline_crossed = true;

			if (p[v1][1] < p[v2][1])
				//make and edge record from vertex[v1] to vertex[v2]
				make_edge_rec(p[v1], p[v2]);
			else
				//make an edge record from vertex[v2] to vertex[v1]
				make_edge_rec(p[v2], p[v1]);
		}

		//move to next edge
		v1 = v2;
	}

	return scanline_crossed;
}

void make_edge_rec(PointA lower, PointA upper)
{
	float dy, factor;

	dy = upper[1] - lower[1];

	//dynamically allocate a new edge. Pointer to the edge is stored in e
	Edge * e = new Edge;

	//calculate the edge value incriments between scan line
	//e->inc = subtract_divide(upper, lower, dy);
	e->inc = (upper - lower) / dy;

	//edge starts on the scanline ceil(lower.y)
	factor = ceil(lower[1]) - lower[1];

	//calculate the starting values for the edge
	//e->p = multiply_add(lower, factor, e->inc);
	e->p = lower + (factor * e->inc);

	//find the last scanline for the edge
	e->yLast = ceil(upper[1]) - 1;

	int index = (int)ceil(lower[1]);

	//insert e into the edge table list of edges starting on scanline
	insert_edge(edgetable[index], e);

	//ceil(lower.y);
}

void add_active_list(int scanline, Edge * &AET)
{
	Edge *p, *q;

	//get the edges starting on this scan line
	p = edgetable[scanline];

	while (p)
	{
		//hold the rest of the list
		q = p->next;
		insert_edge(AET, p);
		p = q;
	}

	//keep the edge table clean -- edges have been transferred
	edgetable[scanline] = 0;
}

void insert_edge(Edge * &linked_list, Edge * e)
{
	/*if (linked_list == nullptr)
	{
	linked_list = e;
	e->next = nullptr;
	return;
	}*/

	Edge *p, *q = linked_list;

	//p leads
	p = linked_list;

	while (p != 0 && (e->p[0] > p->p[0]))
	{
		//step to the next edge
		q = p;
		p = p->next;
	}

	//link the edge into the list after q
	if (q == p)
	{
		e->next = q;
		linked_list = e;
	}
	else
	{
		e->next = p;
		q->next = e;
	}
}

void update_AET(int scanline, Edge * &AET)
{

	//p leads
	Edge *q = AET, *p = AET;

	while (p)
	{
		if (scanline == p->yLast)
		{
			if (p == AET)
			{
				p = p->next;
				delete q;
				AET = p;
				q = AET;
			}
			else
			{
				p = p->next;
				delete_after(q);
			}
		}
		else
		{
			//update the attribute values
			//p->p = add(p->p, p->inc);
			p->p = p->p + p->inc;

			q = p;
			p = p->next;
		}
	}

}

void delete_after(Edge * q)
{
	Edge *p = q->next;

	q->next = p->next;

	delete p;
}

void resort_AET(Edge * &AET)
{
	Edge *q, *p = AET;

	AET = 0;

	while (p)
	{
		q = p->next;
		p->next = 0;
		insert_edge(AET, p);
		p = q;
	}
}

void fill_between_edges(int scanline, Edge * AET)
{
	PointA inc, p;

	Edge *p1, *p2;

	p1 = AET;

	while (p1)
	{
		//get the pair of edges from AET
		p2 = p1->next;

		if (ceil(p1->p[0]) != ceil(p2->p[0]))
		{
			//calculate the attribute incriments along the scanline
			float dx = p2->p[0] - p1->p[0];

			//inc = subtract_divide(p2->p, p1->p, dx);
			inc = (p2->p - p1->p) / dx;
			//calculate the starting values for the edge
			//gives the fractional position of the first pixel crossing
			float factor = ceil(p1->p[0]) - p1->p[0];

			//p = multiply_add(p1->p, factor, inc);
			p = p1->p + (factor * inc);

			float endx = ceil(p2->p[0]);

			while (p[0] < endx)
			{
				float poly_color[3]{ 0, 0, 0 };

				surface_point_values = p;

				surface_point_values = surface_point_values / p[ATTR_CONSTANT];

				surface_shader(poly_color);

				PointH plot_pointh{ p[0], (float)scanline, p[2], p[3] };
				//calculate the color for the pixel and plot it
				//x and z come from the current values, y is the current scanline
				poly_plot(plot_pointh, poly_color);

				//incriment the values
				p = p + inc;

			}
		}

		p1 = p2->next;
	}
}