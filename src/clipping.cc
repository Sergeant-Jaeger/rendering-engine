#include "Clipping.h"

void line_clipping(PointH &p1, string flag)
{
	float BC1[6];
	int kode1 = 0;
	int mask = 1;

	//define BC1
	BC1[0] = p1[0];
	BC1[1] = p1[3] - p1[0];
	BC1[2] = p1[1];
	BC1[3] = p1[3] - p1[1];
	BC1[4] = p1[2];
	BC1[5] = p1[3] - p1[2];

	//define kode1
	for (int i = 0; i < 6; i++)
	{
		if (BC1[i] < 0)
			kode1 |= mask;

		mask <<= 1;
	}

	//if flag is move		
	if (flag == "move")
		goto Cleanup;
	else
	{
		//if kode 0 & kode 1 (trivial reject)
		if (kode0 & kode1)
			goto Cleanup;

		int kode = kode0 | kode1;

		//if kode == 0 (trivial accept)
		if (kode == 0)
		{
			//convert p0 & p1 to device coords
			PointH start_device_vertex, end_device_vertex;

			start_device_vertex = clip_device_xform * p0;

			end_device_vertex = clip_device_xform * p1;

			for (int i = 0; i <= 3; i++)
			{
				start_device_vertex[i] = start_device_vertex[i] / start_device_vertex[3];

				end_device_vertex[i] = end_device_vertex[i] / end_device_vertex[3];
			}

			//draw line
			digital_differential_analyzer(start_device_vertex, end_device_vertex);

			goto Cleanup;
		}
		//else (non-trivial accept)
		else
		{
			//amin = 0.0 and amax = 1.0
			float amin = 0.0;
			float amax = 1.0;
			float a;

			mask = 1;

			//for i < 6
			for (int i = 0; i < 6; i++)
			{
				//if bit i in kode == 1
				if ((kode & mask) != 0)
				{
					//a = BC0[i] / BC0[i] - BC1[i]
					a = BC0[i] / (BC0[i] - BC1[i]);

					//if bit i in kode 0 == 1 (outside to inside)
					if ((kode0 & mask) != 0)
						//amin = max of amin and a
						amin = max(a, amin);
					//else (inside to outside)
					else
						//amax = min of amax and a
						amax = min(a, amax);
				}

				mask <<= 1;
			}
			//if amin < amax
			if (amin < amax)
			{
				PointH p0_prime, p1_prime, start_device_vertex, end_device_vertex;

				p0_prime = p0;
				p1_prime = p1;

				for (int i = 0; i <= 3; i++)
				{
					p0_prime[i] = p0[i] + (amin * (p1[i] - p0[i]));

					p1_prime[i] = p0[i] + (amax * (p1[i] - p0[i]));
				}


				start_device_vertex = clip_device_xform * p0_prime;

				end_device_vertex = clip_device_xform * p1_prime;

				for (int i = 0; i <= 3; i++)
				{
					start_device_vertex[i] = start_device_vertex[i] / start_device_vertex[3];

					end_device_vertex[i] = end_device_vertex[i] / end_device_vertex[3];
				}

				//draw line
				digital_differential_analyzer(start_device_vertex, end_device_vertex);
			}
		}
	}

Cleanup:
	p0 = p1;

	for (int i = 0; i < 6; i++)
		BC0[i] = BC1[i];

	kode0 = kode1;
}

int polygon_clipping(PointA p[], int p_size, PointA clipped_p[])
{
	/*for (int i = 0; i < p_size; i++)
	{
	clipped_p[i] = p[i];
	}

	return p_size;*/

	//

	//Variables:   an array of PointAs for the first point
	//	seen by each clipping pipeline stage
	//	an array of flags to indicate whether the
	//	the pipeline stage has been seen, i.e., whether
	//	the first point is valid or uninitialized garbage
	//
	//	an array of PointA for the last point
	//	seen by each clipping pipeline stage
	//
	//	The size of each of these arrays is the number of stages in
	//	the clipping pipeline, one stage for each clipping boundary.
	//
	//	The output array, the integer count, the first, flag, and
	//	last arrays will be referred to collectively as "extra
	//	stuff "
	//
	//	These arrays should be available to many of the functions
	//	described here.They can either be passed explicitly as
	//	function arguments or defined as global variables to this
	//	module.
	//

	PointA first[BOUNDARY_SIZE];
	bool seen[BOUNDARY_SIZE];
	PointA last[BOUNDARY_SIZE];

	int count = 0;

	Boundary b = left;

	//
	//	The flag array should be initialized.
	//

	for (int i = 0; i < BOUNDARY_SIZE; i++)
		seen[i] = false;

	//	Loop over all the vertex points in pIn
	//	clip a point(pIn[k], FirstBoundary, extra stuff);
	//
	//			 clip the last point(extra stuff);
	//

	for (int i = 0; i < p_size; i++)
	{
		clip_point(p[i], b, clipped_p, count, first, seen, last);
	}

	clip_last_point(clipped_p, count, first, seen, last);

	//	return the count

	return count;
}

void clip_point(PointA p, Boundary b, PointA clipped_p[], int &count, PointA first[], bool seen[], PointA last[])
{
	PointA iPt;

	//if this is the first time a point has been seen at stage b
	//	first[b] = p;
	//Update the flag array as well

	if (!seen[b])
	{
		first[b] = p;
		seen[b] = true;
	}
	//else
	//	// Previous point exists

	//	if the edge defined by p and last[b] crosses boundary b
	//		ipt = intersect(p, last[b], b);
	//send ipt to the next stage of the pipeline or to the
	//	output array depending on b, i.e.
	//	clip a point(iPt, b + 1, extra stuff)
	//	or
	//	pOut[count++] = iPt;
	else
	{
		if (cross(p, last[b], b))
		{
			iPt = intersect(p, last[b], b);

			if (b < back)
			{
				clip_point(iPt, Boundary(b + 1), clipped_p, count, first, seen, last);
			}
			else
			{
				clipped_p[count] = p;
				count++;
			}
		}
	}

	//// Save the most recent vertex seen at this stage.
	//last[b] = p;
	last[b] = p;

	//if p is inside boundary b then
	//	send p to the next stage or to the output array, like above

	if (inside(p, b))
	{
		if (b < back)
			clip_point(p, Boundary(b + 1), clipped_p, count, first, seen, last);
		else
		{
			clipped_p[count] = p;
			count++;
		}
	}
}

void clip_last_point(PointA clipped_p[], int &count, PointA first[], bool seen[], PointA last[])
{
	PointA iPt;

	Boundary b;

	/*Loop over the boundaries with b
	if first[b] exists and the edge defined by first[b] and
	last[b] crosses boundary b then

	ipt = intersect(last[b], first[b], b);

	send ipt to the next stage of the pipeline or to the
	output array*/

	for (b = left; b <= back; b = Boundary(b + 1))
	{
		if (seen[b] && cross(first[b], last[b], b))
		{
			iPt = intersect(last[b], first[b], b);

			if (b < back)
				clip_point(iPt, Boundary(b + 1), clipped_p, count, first, seen, last);
			else
			{
				clipped_p[count] = iPt;
				count++;
			}
		}

	}
}

PointA intersect(PointA p1, PointA p2, Boundary b)
{
	/*Takes two attributed points and a boundary and returns an attributed point.The intersection point can be
	found using the approach taken for line clipping : Calculate alpha using the appropriate boundary coordinates
	for the points and boundary in question and interpolate between the points.Depending on the boundary, the
	formula for alpha does not need all of the boundary coordinates, so don't compute them all. Use only what's
	needed for the given boundary.When interpolating, interpolate all of the coordinates of the points.*/
	PointA iPt;

	float alpha, bc0, bc1;
	//x = 0 left
	//x = 1 right
	//y = 0 bottom
	//y = 1 top
	//z = 0 front
	//z = 1 back
	switch (b)
	{
	case left:
		bc0 = p1[0];
		bc1 = p2[0];
		break;
	case right:
		bc0 = p1[3] - p1[0];
		bc1 = p2[3] - p2[0];
		break;
	case bottom:
		bc0 = p1[1];
		bc1 = p2[1];
		break;
	case top:
		bc0 = p1[3] - p1[1];
		bc1 = p2[3] - p2[1];
		break;
	case front:
		bc0 = p1[2];
		bc1 = p2[2];
		break;
	case back:
		bc0 = p1[3] - p1[2];
		bc1 = p2[3] - p2[2];
		break;
	}

	alpha = bc0 / (bc0 - bc1);

	for (int i = 0; i < ATTR_SIZE; i++)
	{
		iPt[i] = p1[i] + alpha * (p2[i] - p1[i]);
	}

	return iPt;
}

bool inside(PointA p, Boundary b)
{
	bool result;

	switch (b)
	{
	case left:
		result = 0 < p[0];
		break;
	case right:
		result = 0 < (p[3] - p[0]);
		break;
	case bottom:
		result = 0 < p[1];
		break;
	case top:
		result = 0 < (p[3] - p[1]);
		break;
	case front:
		result = 0 < p[2];
		break;
	case back:
		result = 0 < (p[3] - p[2]);
		break;
	}

	return result;
}

bool cross(PointA p1, PointA p2, Boundary b)
{
	if (inside(p1, b) == inside(p2, b))
		return false;
	else
		return true;
}