#include "pipelines.h"
#include <iostream>
#include <iomanip>

using namespace std;

void point_pipeline(PointH &homogenous_point)
{
	PointH current_pointh;

	current_pointh = current_xform * homogenous_point;

	PointH world_clip_pointh;

	world_clip_pointh = world_clip_xform * current_pointh;

	if (world_clip_pointh[0] > 0 && world_clip_pointh[0] < world_clip_pointh[3] &&
		world_clip_pointh[1] > 0 && world_clip_pointh[1] < world_clip_pointh[3] &&
		world_clip_pointh[2] > 0 && world_clip_pointh[2] < world_clip_pointh[3])
	{
		PointH device_pointh;

		device_pointh = clip_device_xform * world_clip_pointh;

		for (int i = 0; i <= 3; i++)
			device_pointh[i] = device_pointh[i] / device_pointh[3];

		pixel_plot(device_pointh);
	}
}

void line_pipeline(PointH &vertex, string flag)
{
	PointH current_vertex;

	current_vertex = current_xform * vertex;

	PointH world_clip_vertex;

	world_clip_vertex = world_clip_xform * current_vertex;

	line_clipping(world_clip_vertex, flag);
}

int polygon_pipeline(PointA p, int end_flag)
{
	//cout << "Poly pipeline" << endl;

	PointH geom, norm;
	PointH dev;

	const int MAX_VERTEX_LIST_SIZE = 50;
	static PointA vertex_list[MAX_VERTEX_LIST_SIZE];
	static PointA clipped_list[MAX_VERTEX_LIST_SIZE];
	static int n_vertex = 0;

	int i;

	// Run geometry through current transform
	/*geom[0] = p.coord[0];
	geom[1] = p.coord[1];
	geom[2] = p.coord[2];
	geom[3] = p.coord[3];*/

	geom = p;

	norm[0] = p[ATTR_NX];
	norm[1] = p[ATTR_NY];
	norm[2] = p[ATTR_NZ];
	norm[3] = 0;

	geom = current_xform * geom;

	p[ATTR_WORLD_X] = geom[0];
	p[ATTR_WORLD_Y] = geom[1];
	p[ATTR_WORLD_Z] = geom[2];

	norm = normal_xform * norm;

	p[ATTR_NX] = norm[0];
	p[ATTR_NY] = norm[1];
	p[ATTR_NZ] = norm[2];

	// Run through world to clip
	geom = world_clip_xform * geom;

	p = geom;

	p[ATTR_CONSTANT] = 1.0;

	/*p.coord[0] = geom[0];
	p.coord[1] = geom[1];
	p.coord[2] = geom[2];
	p.coord[3] = geom[3];*/

	// Store in vertex list
	if (n_vertex == MAX_VERTEX_LIST_SIZE)
		return -1;  // Overflow

	vertex_list[n_vertex] = p;
	n_vertex++;

	if (end_flag == 1)  // Move along to the next vertex
		return 0;

	if ((n_vertex = polygon_clipping(vertex_list, n_vertex, clipped_list)))
	{
		// There's something left! --- Let's draw it

		// Pre process vertex list
		for (i = 0; i < n_vertex; i++)
		{
			// Convert geometry to device coordinates
			/*dev[0] = clipped_list[i].coord[0];
			dev[1] = clipped_list[i].coord[1];
			dev[2] = clipped_list[i].coord[2];
			dev[3] = clipped_list[i].coord[3];*/
			
			dev = clipped_list[i];

			dev = clip_device_xform * dev;

			/*clipped_list[i].coord[0] = dev[0];
			clipped_list[i].coord[1] = dev[1];*/
			// clipped_list[i].coord[2] = dev[2];  // Superfluous
			// clipped_list[i].coord[3] = dev[3];

			clipped_list[i] = dev;

			// Divide geometry by w.
			for (int j = 0; j < ATTR_SIZE; j++)
					clipped_list[i][j] /= dev[3];

			/*clipped_list[i][0] /= clipped_list[i][3];
			clipped_list[i][1] /= clipped_list[i][3];
			clipped_list[i][2] /= clipped_list[i][3];*/


		}
		PointH poly_normal_world(polygon_normal[0], polygon_normal[1], polygon_normal[2], 0);

		poly_normal_world = normal_xform * poly_normal_world;

		for (int i = 0; i < 3; i++)
			polygon_normal[i] = poly_normal_world[i];

		scan_convert(clipped_list, n_vertex);
	}

	// Reset structures for next polygon

	n_vertex = 0;

	return 0;
}