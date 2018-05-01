#include "lighting.h"

//ambient
//Ka * Ia *Cs
void ambient_lighting(float color[3])
{
	for (int i = 0; i < 3; i++)
		color[i] += ambient_k * ambient_l[i] * surface_color[i];
}

//diffuse
//Kd * Cs * Sigmai(N dot Li) * Ii

void diffuse_lighting(float color[3])
{
	Vector n, l;

	float far_lights[3]{ 0, 0, 0 };
	float point_lights[3]{ 0, 0, 0 };

	float nl;

	if (interpolation_flag && vertex_n_flag)
	{
		n[0] = surface_point_values[ATTR_NX];
		n[1] = surface_point_values[ATTR_NY];
		n[2] = surface_point_values[ATTR_NZ];
	}
	else
		n = polygon_normal;

	n.normalize();
	
	if (!far_l.empty())
	{
		for (unsigned int j = 0; j < far_l.size(); j++)
		{
			l[0] = far_l[j][0];
			l[1] = far_l[j][1];
			l[2] = far_l[j][2];

			l.normalize();

			nl = n.dot_product(l);

			if (nl >= 0)
				for (int i = 0; i < 3; i++)
					far_lights[i] += nl * far_l[j][i + 3];
		}
	}

	if (!point_l.empty())
	{
		for (unsigned int j = 0; j < point_l.size(); j++)
		{
			l[0] = point_l[j][0] - surface_point_values[ATTR_WORLD_X];
			l[1] = point_l[j][1] - surface_point_values[ATTR_WORLD_Y];
			l[2] = point_l[j][2] - surface_point_values[ATTR_WORLD_Z];

			float mag_squared = l.magnitude_squared();

			l.normalize();

			nl = n.dot_product(l);

			if (nl >= 0)
				for (int i = 0; i < 3; i++)
					point_lights[i] += nl * (point_l[j][i + 3] / mag_squared);
		}
	}

	for (int i = 0; i < 3; i++)
		color[i] += far_lights[i] + point_lights[i];
}

//specular
//Ks * Cspec *Sigmai(V dot R)^Ns * Ii

void specular_lighting(float color[3])
{
	Vector n, l, v, r;

	float far_lights[3]{ 0, 0, 0 };
	float point_lights[3]{ 0, 0, 0 };

	float vr, vn;

	if (interpolation_flag && vertex_n_flag)
	{
		n[0] = surface_point_values[ATTR_NX];
		n[1] = surface_point_values[ATTR_NY];
		n[2] = surface_point_values[ATTR_NZ];
	}
	else
		n = polygon_normal;

	n.normalize();

	if (!far_l.empty())
	{
		for (unsigned int j = 0; j < far_l.size(); j++)
		{
			l[0] = far_l[j][0];
			l[1] = far_l[j][1];
			l[2] = far_l[j][2];

			l.normalize();

			v[0] = cam_eye[0] - surface_point_values[ATTR_WORLD_X];
			v[1] = cam_eye[1] - surface_point_values[ATTR_WORLD_Y];
			v[2] = cam_eye[2] - surface_point_values[ATTR_WORLD_Z];

			v.normalize();

			vn = v.dot_product(n);

			if (vn >= 0)
			{
				r = compute_reflection_vector(l, n);

				r.normalize();

				vr = v.dot_product(r);

				float vr_exponent = pow(vr, specular_exponent);

				if (vr >= 0)
					for (int i = 0; i < 3; i++)
						far_lights[i] += vr_exponent * far_l[j][i + 3];
			}
		}
	}

	if (!point_l.empty())
	{
		for (unsigned int j = 0; j < point_l.size(); j++)
		{
			l[0] = point_l[j][0] - surface_point_values[ATTR_WORLD_X];
			l[1] = point_l[j][1] - surface_point_values[ATTR_WORLD_Y];
			l[2] = point_l[j][2] - surface_point_values[ATTR_WORLD_Z];

			float mag_squared = l.magnitude_squared();

			l.normalize();

			v[0] = cam_eye[0] - surface_point_values[ATTR_WORLD_X];
			v[1] = cam_eye[1] - surface_point_values[ATTR_WORLD_Y];
			v[2] = cam_eye[2] - surface_point_values[ATTR_WORLD_Z];

			v.normalize();

			vn = v.dot_product(n);
			 
			if (vn >= 0)
			{
				r = compute_reflection_vector(l, n);

				r.normalize();

				vr = v.dot_product(r);

				if (vr >= 0)
					for(int i = 0; i < 3; i++)
						point_lights[i] += (pow(vr, specular_exponent)) * (point_l[j][i + 3] / mag_squared);
			}
		}
	}

	for(int i = 0; i < 3; i++)
		color[i] += far_lights[i] + point_lights[i];
}

Vector compute_reflection_vector(Vector l, Vector n)
{
	float nl_scalar = n.dot_product(l);

	Vector n2(n[0], n[1], n[2]);

	//Vector n2(n[0] / n.magnitude_squared(), n[1] / n.magnitude_squared(), n[2] / n.magnitude_squared());

	return ((2 * nl_scalar) * n2) - l;
}