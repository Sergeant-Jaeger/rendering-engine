#include "Shapes.h"

void point_set(int nvertex, const float * vertex)
{
	PointH pointh;

	for (int i = 0; i < nvertex; i++)
	{
		for (int j = 0; j < 3; j++)
			pointh[j] = vertex[(3 * i) + j];

		point_pipeline(pointh);
	}
}

//bresenham replaced by DDA

//void bresenham_line(const float start[], const float end[])
//{
//	int x = (int)start[0];
//	int endX = (int)end[0];
//	int dX = endX - x;
//
//	int y = (int)start[1];
//	int endY = (int)end[1];
//	int dY = endY - y;
//
//	if (dX >= 0 && dY >= 0)
//	{
//		if (abs(dX) >= abs(dY))
//		{
//			int p = (2 * dY) - dX;
//
//			while (x <= endX)
//			{
//				
//				rd_write_pixel(x, y, fg_color);
//
//				if (p < 0)
//					p += 2 * dY;
//				else
//				{
//					y++;
//
//					p += (2 * dY) - (2 * dX);
//				}
//
//				x++;
//			}
//		}
//		else
//		{
//			int p = (2 * dX) - dY;
//
//			while (y <= endY)
//			{
//				rd_write_pixel(x, y, fg_color);
//
//				if (p < 0)
//					p += 2 * dX;
//				else
//				{
//					x++;
//
//					p += (2 * dX) - (2 * dY);
//				}
//
//				y++;
//			}
//		}
//
//	}
//	else if (dX >= 0 && dY < 0)
//	{
//		if (abs(dX) >= abs(dY))
//		{
//			int p = (2 * (-dY)) - dX;
//
//			while (x <= endX)
//			{
//				rd_write_pixel(x, y, fg_color);
//
//				if (p < 0)
//					p += 2 * (-dY);
//				else
//				{
//					y--;
//
//					p += (2 * (-dY)) - (2 * dX);
//				}
//
//				x++;
//			}
//		}
//		else
//		{
//			int p = (2 * dX) + dY;
//
//			while (y >= endY)
//			{
//				rd_write_pixel(x, y, fg_color);
//
//				if (p < 0)
//					p += 2 * dX;
//				else
//				{
//					x++;
//
//					p += (2 * dX) - (2 * (-dY));
//				}
//
//				y--;
//			}
//		}
//
//	}
//	else if (dX < 0 && dY >= 0)
//	{
//		if (abs(dX) >= abs(dY))
//		{
//			int p = (2 * dY) + dX;
//
//			while (x >= endX)
//			{
//				rd_write_pixel(x, y, fg_color);
//
//				if (p < 0)
//					p += 2 * dY;
//				else
//				{
//					y++;
//
//					p += (2 * dY) - (2 * (-dX));
//				}
//
//				x--;
//			}
//		}
//		else
//		{
//			int p = (2 * (-dX)) - dY;
//
//			while (y <= endY)
//			{
//				rd_write_pixel(x, y, fg_color);
//
//				if (p < 0)
//					p += 2 * (-dX);
//				else
//				{
//					x--;
//
//					p += (2 * (-dX)) - (2 * dY);
//				}
//
//				y++;
//			}
//		}
//
//	}
//	else
//	{
//		if (abs(dX) >= abs(dY))
//		{
//			int p = (2 * (-dY)) + dX;
//
//			while (x >= endX)
//			{
//				rd_write_pixel(x, y, fg_color);
//
//				if (p < 0)
//					p += 2 * (-dY);
//				else
//				{
//					y--;
//
//					p += (2 * (-dY)) + (2 * dX);
//				}
//
//				x--;
//			}
//		}
//		else
//		{
//			int p = (2 * (-dX)) + dY;
//
//			while (y >= endY)
//			{
//				rd_write_pixel(x, y, fg_color);
//
//				if (p < 0)
//					p += 2 * (-dX);
//				else
//				{
//					x--;
//
//					p += (2 * (-dX)) + (2 * dY);
//				}
//
//				y--;
//			}
//		}
//
//	}
//}

void digital_differential_analyzer(PointH &start, PointH &end)
{
	int nsteps;
	//p = p0 + t * (p1 - p0) unnecessary?

	//dx = xend - xstart
	int dx = (int)end[0] - (int)start[0];
	//dy = yend - ystart
	int dy = (int)end[1] - (int)start[1];
	//dz = zend - zstart
	float dz = end[2] - start[2];

	//if abs dx > abs dy
	if (abs(dx) > abs(dy))
		//nsteps = abs dx
		nsteps = abs(dx);
	//else
	else
		//nsteps = abs dy
		nsteps = abs(dy);

	//inc = dp / nsteps
	float xinc = (float)dx / nsteps;
	float yinc = (float)dy / nsteps;
	float zinc = dz / nsteps;

	//if nsteps == 0
	if (nsteps == 0)
	{
		//if z1 > z0 
		if (end[2] >= start[2])
			//plot P0
			pixel_plot(start);

		//else
		else
			//plot p1
			pixel_plot(end);
	}
	else
	{
		//p = p0
		PointH p;

		p = start;

		//for i < nsteps
		for (int i = 0; i <= nsteps; i++)
		{
			pixel_plot(p);
			
			//p += inc
			p[0] += xinc;
			p[1] += yinc;
			p[2] += zinc;
		}
	}
}

void midpoint_circle(const float center[3], const float radius)
{
	int x = 0;

	int y = (int)radius;

	int p = 1 - y;

	while (y >= x)
	{
		rd_write_pixel(x + center[0], y + center[1], fg_color);
		rd_write_pixel(x + center[0], (-y) + center[1], fg_color);
		rd_write_pixel((-x) + center[0], y + center[1], fg_color);
		rd_write_pixel((-x) + center[0], (-y) + center[1], fg_color);
		rd_write_pixel(y + center[0], x + center[1], fg_color);
		rd_write_pixel(y + center[0], (-x) + center[1], fg_color);
		rd_write_pixel((-y) + center[0], x + center[1], fg_color);
		rd_write_pixel((-y) + center[0], (-x) + center[1], fg_color);

		x++;

		if (p > 0)
		{
			y--;

			p += (2 * x) - (2 * y) + 1;
		}
		else
			p += (2 * x) + 1;
	}
}

void polygon_set(const float * vertex, int nface, const int * face)
{
	vertex_c_flag = false;

	vertex_t_flag = false;

	vertex_n_flag = false;

	PointH initial_vertex;
	PointH draw_vertex;
	PointA avertex;
	int l = 0;
	vector<Vector3> normal_vectors;

	for (int i = 0; i < nface; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			initial_vertex[j] = vertex[(3 * face[l]) + j];
		}

		for (int j = 0; j < 4; j++)
			avertex[j] = initial_vertex[j];

		normal_vectors.push_back(Vector3(avertex[0], avertex[1], avertex[2]));

		//line_pipeline(initial_vertex, "move");
		polygon_pipeline(avertex, 1);

		l++;

		while (face[l] != -1)
		{
			for (int k = 0; k < 3; k++)
				draw_vertex[k] = vertex[(3 * face[l]) + k];

			for (int j = 0; j < 4; j++)
				avertex[j] = draw_vertex[j];

			normal_vectors.push_back(Vector3(avertex[0], avertex[1], avertex[2]));

			//line_pipeline(draw_vertex, "draw");
			if (face[l + 1] == -1)
			{
				polygon_normal = (normal_vectors[2] - normal_vectors[0]).cross_product(normal_vectors[normal_vectors.size() - 1] - normal_vectors[1]);
				//polygon_normal = (normal_vectors[normal_vectors.size() - 1] - normal_vectors[1]).cross_product(normal_vectors[2] - normal_vectors[0]);

				normal_vectors.clear();

				polygon_pipeline(avertex, 0);
			}
			else
			{				
				polygon_pipeline(avertex, 1);
			}

			l++;
		}

		//line_pipeline(initial_vertex, "draw");

		l++;
	}
}

void cube()
{
	vertex_c_flag = false;

	vertex_t_flag = false;

	vertex_n_flag = false;

	PointA aa0, aa1, ab0, ab1, ac0, ac1, ad0, ad1;

	PointH a0(-1, -1, -1, 1), 
		a1(-1, -1, 1, 1), 
		b0(1, -1, -1, 1), 
		b1(1, -1, 1, 1), 
		c0(1, 1, -1, 1), 
		c1(1, 1, 1, 1), 
		d0(-1, 1, -1, 1), 
		d1(-1, 1, 1, 1); 

	aa0 = a0;
	aa1 = a1;
	ab0 = b0;
	ab1 = b1;
	ac0 = c0;
	ac1 = c1;
	ad0 = d0;
	ad1 = d1;

	//back - good

	polygon_pipeline(aa0, 1);
	polygon_pipeline(ad0, 1);
	polygon_pipeline(ac0, 1);

	polygon_normal[0] = 0;
	polygon_normal[1] = 0;
	polygon_normal[2] = -1;

	polygon_pipeline(ab0, 0);

	

	//right - good

	polygon_pipeline(ac1, 1);
	polygon_pipeline(ab1, 1);
	polygon_pipeline(ab0, 1);

	polygon_normal[0] = 1;
	polygon_normal[1] = 0;
	polygon_normal[2] = 0;

	polygon_pipeline(ac0, 0);

	//left - good

	polygon_pipeline(aa0, 1);
	polygon_pipeline(aa1, 1);
	polygon_pipeline(ad1, 1);

	polygon_normal[0] = -1;
	polygon_normal[1] = 0;
	polygon_normal[2] = 0;

	polygon_pipeline(ad0, 0);

	//top - good

	polygon_pipeline(ad1, 1);
	polygon_pipeline(ac1, 1);
	polygon_pipeline(ac0, 1);

	polygon_normal[0] = 0;
	polygon_normal[1] = 1;
	polygon_normal[2] = 0;

	polygon_pipeline(ad0, 0);

	//bottom - good

	polygon_pipeline(aa0, 1);
	polygon_pipeline(ab0, 1);
	polygon_pipeline(ab1, 1);

	polygon_normal[0] = 0;
	polygon_normal[1] = -1;
	polygon_normal[2] = 0;

	polygon_pipeline(aa1, 0);

	//front - good

	polygon_pipeline(aa1, 1);
	polygon_pipeline(ab1, 1);
	polygon_pipeline(ac1, 1);

	polygon_normal[0] = 0;
	polygon_normal[1] = 0;
	polygon_normal[2] = 1;

	polygon_pipeline(ad1, 0);
}

void sphere(float radius, float zmin, float zmax, float thetamax)
{
	vertex_c_flag = false;

	vertex_t_flag = false;

	vertex_n_flag = true;

	int nsteps = 24;

	float theta0;
	float theta1;
	float phi0;
	float phi1;

	PointA ap1, ap2, ap3, ap4;

	for (int i = 0; i < nsteps; i++)
	{
		phi0 = ((float)i / nsteps) * (2 * M_PI);
		phi1 = (((float)i + 1) / nsteps) * (2 * M_PI);

		for (int j = 0; j < 2 * nsteps; j++)
		{
			theta0 = ((float)j / nsteps) * (2 * M_PI);
			theta1 = (((float)j + 1) / nsteps) * (2 * M_PI);

			PointH p1(radius * cos(phi0) * cos(theta0), radius * cos(phi0) * sin(theta0), radius * sin(phi0), 1);
			PointH p2(radius * cos(phi0) * cos(theta1), radius * cos(phi0) * sin(theta1), radius * sin(phi0), 1);
			PointH p3(radius * cos(phi1) * cos(theta1), radius * cos(phi1) * sin(theta1), radius * sin(phi1), 1);
			PointH p4(radius * cos(phi1) * cos(theta0), radius * cos(phi1) * sin(theta0), radius * sin(phi1), 1);

			for (int i = 0; i < 4; i++)
			{
				ap1[i] = p1[i];
				ap2[i] = p2[i];
				ap3[i] = p3[i];
				ap4[i] = p4[i];
			}

			ap1[ATTR_NX] = p1[0];
			ap1[ATTR_NY] = p1[1];
			ap1[ATTR_NZ] = p1[2];

			ap2[ATTR_NX] = p2[0];
			ap2[ATTR_NY] = p2[1];
			ap2[ATTR_NZ] = p2[2];

			ap3[ATTR_NX] = p3[0];
			ap3[ATTR_NY] = p3[1];
			ap3[ATTR_NZ] = p3[2];

			ap4[ATTR_NX] = p4[0];
			ap4[ATTR_NY] = p4[1];
			ap4[ATTR_NZ] = p4[2];

			polygon_pipeline(ap1, 1);
			polygon_pipeline(ap2, 1);
			polygon_pipeline(ap3, 1);

			Vector3 v1(p1[0], p1[1], p1[2]);
			Vector3 v2(p2[0], p2[1], p2[2]);
			Vector3 v3(p3[0], p3[1], p3[2]);
			Vector3 v4(p4[0], p4[1], p4[2]);

			polygon_normal = (v3 - v1).cross_product(v4 - v2);

			polygon_pipeline(ap4, 0);
		}
	}
}

void cone(float height, float radius, float thetamax)
{
	vertex_c_flag = false;

	vertex_t_flag = false;

	vertex_n_flag = true;

	int nsteps = 24;
	float theta1;
	float theta2;

	float nz = pow(radius, 2) / height;

	PointH xy1, xy2, tip1;
	PointA ap1, ap2, atip1, atip2;

	tip1[2] = height;


	for (int i = 0; i <= nsteps; i++)
	{
		theta1 = ((float)i / nsteps) * (2 * M_PI);
		theta2 = (((float)i + 1) / nsteps) * (2 * M_PI);

		xy1[0] = radius * cos(theta1);
		xy1[1] = radius * sin(theta1);

		xy2[0] = radius * cos(theta2);
		xy2[1] = radius * sin(theta2);

		for (int i = 0; i < 4; i++)
		{
			ap1[i] = xy1[i];
			ap2[i] = xy2[i];
			atip1[i] = tip1[i];
			atip2[i] = tip1[i];
		}
		
		ap1[ATTR_NX] = xy1[0];
		ap1[ATTR_NY] = xy1[1];
		ap1[ATTR_NZ] = nz;

		ap2[ATTR_NX] = xy2[0];
		ap2[ATTR_NY] = xy2[1];
		ap2[ATTR_NZ] = nz;

		atip1[ATTR_NX] = xy2[0];
		atip1[ATTR_NY] = xy2[1];
		atip1[ATTR_NZ] = nz;

		atip2[ATTR_NX] = xy1[0];
		atip2[ATTR_NY] = xy1[1];
		atip2[ATTR_NZ] = nz;


		polygon_pipeline(ap1, 1);
		polygon_pipeline(ap2, 1);
		polygon_pipeline(atip2, 1);

		Vector3 v1(ap1[0], ap1[1], ap1[2]);
		Vector3 v2(ap2[0], ap2[1], ap2[2]);
		Vector3 v3(atip2[0], atip2[1], atip2[2]);
		Vector3 v4(atip1[0], atip1[1], atip1[2]);

		polygon_normal = (v3 - v1).cross_product(v4 - v2);

		polygon_pipeline(atip1, 0);
	}
}

void cylinder(float radius, float zmin, float zmax, float thetamax)
{
	vertex_c_flag = false;

	vertex_t_flag = false;

	vertex_n_flag = true;

	int nsteps = 24;
	float theta1;
	float theta2;

	PointH xy1_min, xy2_min, xy1_max, xy2_max;

	PointA a1min, a1max, a2min, a2max;

	for (int i = 0; i <= nsteps; i++)
	{
		theta1 = ((float)i / nsteps) * (2 * M_PI);
		theta2 = (((float)i + 1) / nsteps) * (2 * M_PI);

		xy1_min[0] = radius * cos(theta1);
		xy1_min[1] = radius * sin(theta1);
		xy1_min[2] = zmin;

		xy1_max[0] = radius * cos(theta1);
		xy1_max[1] = radius * sin(theta1);
		xy1_max[2] = zmax;

		xy2_min[0] = radius * cos(theta2);
		xy2_min[1] = radius * sin(theta2);
		xy2_min[2] = zmin;

		xy2_max[0] = radius * cos(theta2);
		xy2_max[1] = radius * sin(theta2);
		xy2_max[2] = zmax;

		for (int i = 0; i < 4; i++)
		{
			a1min[i] = xy1_min[i];
			a1max[i] = xy1_max[i];
			a2min[i] = xy2_min[i];
			a2max[i] = xy2_max[i];
		}

		a1min[ATTR_NX] = cos(theta1);
		a1min[ATTR_NY] = sin(theta1);
		a1min[ATTR_NZ] = 0;

		a2min[ATTR_NX] = cos(theta2);
		a2min[ATTR_NY] = sin(theta2);
		a2min[ATTR_NZ] = 0;

		a2max[ATTR_NX] = cos(theta2);
		a2max[ATTR_NY] = sin(theta2);
		a2max[ATTR_NZ] = 0;

		a1max[ATTR_NX] = cos(theta1);
		a1max[ATTR_NY] = sin(theta1);
		a1max[ATTR_NZ] = 0;

		polygon_pipeline(a1min, 1);
		polygon_pipeline(a2min, 1);
		polygon_pipeline(a2max, 1);

		Vector3 v1(a1min[0], a1min[1], a1min[2]);
		Vector3 v2(a2min[0], a2min[1], a2min[2]);
		Vector3 v3(a2max[0], a2max[1], a2max[2]);
		Vector3 v4(a1max[0], a1max[1], a1max[2]);

		polygon_normal = (v3 - v1).cross_product(v4 - v2);

		polygon_pipeline(a1max, 0);
	}
}

void disk(float height, float radius, float theta)
{
	vertex_c_flag = false;

	vertex_t_flag = false;

	vertex_n_flag = true;

	int nsteps = 24;
	float theta1;
	float theta2;

	PointH xy1, xy2, center;

	PointA ap1, ap2, acenter1, acenter2;

	center[2] = height;

	for (int i = 0; i <= nsteps; i++)
	{
		theta1 = ((float)i / nsteps) * (2 * M_PI);
		theta2 = (((float)i + 1) / nsteps) * (2 * M_PI);

		xy1[0] = radius * cos(theta1);
		xy1[1] = radius * sin(theta1);
		xy1[2] = height;

		xy2[0] = radius * cos(theta2);
		xy2[1] = radius * sin(theta2);
		xy2[2] = height;

		for (int i = 0; i < 4; i++)
		{
			ap1[i] = xy1[i];
			ap2[i] = xy2[i];
			acenter1[i] = center[i];
			acenter2[i] = center[i];
		}

		ap1[ATTR_NX] = 0;
		ap1[ATTR_NY] = 0;
		ap1[ATTR_NZ] = 1;

		ap2[ATTR_NX] = 0;
		ap2[ATTR_NY] = 0;
		ap2[ATTR_NZ] = 1;

		acenter2[ATTR_NX] = 0;
		acenter2[ATTR_NY] = 0;
		acenter2[ATTR_NZ] = 1;

		acenter1[ATTR_NX] = 0;
		acenter1[ATTR_NY] = 0;
		acenter1[ATTR_NZ] = 1;

		polygon_pipeline(ap1, 1);
		polygon_pipeline(ap2, 1);
		polygon_pipeline(acenter2, 1);

		Vector3 v1(ap1[0], ap1[1], ap1[2]);
		Vector3 v2(ap2[0], ap2[1], ap2[2]);
		Vector3 v3(acenter2[0], acenter2[1], acenter2[2]);
		Vector3 v4(acenter1[0], acenter1[1], acenter1[2]);

		polygon_normal = (v3 - v1).cross_product(v4 - v2);

		polygon_pipeline(acenter1, 0);
	}
}