#ifndef GLOBALS_H
#define GLOBALS_H

#include <stack>
#include <vector>
#include "Point.h"
#include "PointH.h"
#include "PointA.h"
#include "Vector3.h"
#include "XForm.h"
#include "LightA.h"
#include "LightP.h"
#include "LightF.h"
#include "Edge.h"
#include "rd_display.h"
#include "Shaders.h"

using std::stack;
using std::vector;

extern float fg_color[3];

extern int glbl_frame;

extern float bg_color[3];

extern int** display_image;

extern float seed_color[3];

extern stack <XForm> xform_stack;

extern XForm current_xform;

extern XForm world_camera_xform;

extern XForm camera_clip_xform;

extern XForm world_clip_xform;

extern XForm clip_device_xform;

extern Point cam_eye;

extern Point cam_at;

extern Vector3 cam_up;

extern double cam_fov;

extern double cam_near;

extern double cam_far;

extern double aspect_ratio;

extern PointH old_vertex;

extern PointH p0;

extern float BC0[BOUNDARY_SIZE];

extern int kode0;

extern double** zbuffer;

extern Edge** edgetable;

extern LightA ambient_l;

extern vector<LightF> far_l;

extern vector<LightP> point_l;

extern float ambient_k;

extern float diffuse_k;

extern float specular_k;

extern float specular_exponent;

extern float surface_color[3];

extern float specular_color[3];

extern bool vertex_c_flag;

extern bool vertex_n_flag;

extern bool vertex_t_flag;

extern bool interpolation_flag;

extern Vector3 viewing_vector;

extern Vector3 polygon_normal;

extern PointA surface_point_values;

extern XForm normal_xform;

extern void(*surface_shader)(float[3]);

void z_buffer();

void z_buffer_cleanup();

void edge_table();

void edge_table_cleanup();

#endif /*GLOBALS_H*/