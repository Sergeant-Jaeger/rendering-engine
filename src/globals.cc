#include "Globals.h"
#include <iostream>
#include <iomanip>

using namespace std;

float fg_color[3] = { 1, 1, 1 };

float bg_color[3] = { 0, 0, 0 };

int glbl_frame;

int** display_image;

float seed_color[3];

stack <XForm> xform_stack;

XForm current_xform;

XForm world_camera_xform;

XForm camera_clip_xform;

XForm world_clip_xform;

XForm clip_device_xform;

Point cam_eye;

Point cam_at(0, 0, -1);

Vector3 cam_up(0, 1, 0);

double cam_fov = 90.0;

double cam_near = 1.0;

double cam_far = 1.0e+09;

double aspect_ratio = (double)display_xSize / (double)display_ySize;

PointH p0;

float BC0[BOUNDARY_SIZE];

int kode0;

double** zbuffer = nullptr;

Edge** edgetable = nullptr;

LightA ambient_l( 1, 1, 1 );

vector<LightF> far_l;

vector<LightP> point_l;

float ambient_k = 1;

float diffuse_k = 0;

float specular_k = 0;

float specular_exponent = 10;

float surface_color[3]{ 1, 1, 1 };

float specular_color[3]{ 1, 1, 1 };

bool vertex_c_flag = false;

bool vertex_n_flag = false;

bool vertex_t_flag = false;

bool interpolation_flag = true;

Vector3 viewing_vector;

Vector3 polygon_normal;

PointA surface_point_values;

XForm normal_xform;

void(*surface_shader)(float[3]) = matte;

void z_buffer()
{
	if (zbuffer == nullptr)
	{
		zbuffer = new double*[display_ySize];

		for (int i = 0; i < display_ySize; i++)
		{
			zbuffer[i] = new double[display_xSize];
		}
	}
	for (int i = 0; i < display_ySize; i++)
		for (int j = 0; j < display_xSize; j++)
			zbuffer[i][j] = 1.0;

	for (int i = 0; i < display_ySize; i++)
		for (int j = 0; j < display_xSize; j++)
			if (zbuffer[i][j] != 1.0)
				cout << "Bad" << endl;
}

void z_buffer_cleanup()
{
	for (int i = 0; i < display_ySize; i++)
	{
		delete[] zbuffer[i];
	}

	delete[] zbuffer;
}

void edge_table()
{
	if (edgetable == nullptr)
		edgetable = new Edge*[display_ySize];
}

void edge_table_cleanup()
{
	//cout << "edge table cleanup" << endl;

	delete[] edgetable;

	edgetable = nullptr;

}