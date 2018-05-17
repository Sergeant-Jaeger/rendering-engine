#include "rd_direct.h"
//#include <iostream>
//#include <iomanip>

using namespace std;

REDirect::~REDirect()
{
	//cout << "destructor" << endl;
}

int REDirect::rd_display(const string &name, const string &type, const string &mode)
{
	//cout << "rd_display" << endl;
	return RD_OK;
}

int REDirect::rd_format(int xresolution, int yresolution)
{
	//cout << "rd_format" << endl;

	display_xSize = xresolution;

	display_ySize = yresolution;

	return RD_OK;
}

int REDirect::rd_frame_begin(int frame_no)
{
	//cout << "rd_frame_begin" << endl;

	glbl_frame = frame_no;

	return RD_OK;
}

int REDirect::rd_world_begin(void)
{
	//cout << "rd_world_begin" << endl;

	rd_disp_init_frame(glbl_frame);

	current_xform.identity_matrix();

	normal_xform.identity_matrix();

	world_camera_xform = world_to_camera(cam_eye, cam_at, cam_up);

	camera_clip_xform = camera_to_clip(cam_fov, cam_near, cam_far, (float)display_xSize / (float)display_ySize);;
	
	world_clip_xform = camera_clip_xform * world_camera_xform;
	
	clip_device_xform = clip_to_device(display_xSize, display_ySize);

	z_buffer();

	edge_table();

	return RD_OK;
}

int REDirect::rd_world_end(void)
{
	//cout << "rd_world_end" << endl;

	rd_disp_end_frame();

	return RD_OK;
}

int REDirect::rd_frame_end(void)
{
	//cout << "rd_frame_end" << endl;

	rd_disp_end_frame();

	return RD_OK;
}

int REDirect::rd_color(const float color[])
{
	//cout << "rd_color" << endl;

	for (int i = 0; i < 3; i++)
	{
		fg_color[i] = color[i];
		surface_color[i] = color[i];
	}

	return RD_OK;
}

int REDirect::rd_background(const float color[])
{
	//cout << "rd_background" << endl;

	bg_color[0] = color[0];
	bg_color[1] = color[1];
	bg_color[2] = color[2];

	rd_set_background(bg_color);

	return RD_OK;
}

int REDirect::rd_point(const float p[3])
{
	PointH homogenous_point(p[0], p[1], p[2], 1);

	point_pipeline(homogenous_point);

	return RD_OK;
}

int REDirect::rd_line(const float start[3], const float end[3])
{
	PointH start_pointh(start[0], start[1], start[2], 1);

	PointH end_pointh(end[0], end[1], end[2], 1);

	line_pipeline(start_pointh, "move");

	line_pipeline(end_pointh, "draw");

	return RD_OK;
}

int REDirect::rd_circle(const float center[3], const float radius)
{
	midpoint_circle(center, radius);

	return RD_OK;
}

int REDirect::rd_fill(const float seed_point[3])
{
	rd_read_pixel(seed_point[0], seed_point[1], seed_color);

	area_fill((int)seed_point[0], (int)seed_point[1]);

	return RD_OK;
}

int REDirect::rd_translate(const float offset[3])
{
	//cout << "rd_translate" << endl;

	translate_matrix(current_xform, offset[0], offset[1], offset[2]);

	//inv_translate_matrix(normal_xform, offset[0], offset[1], offset[2]);

	return RD_OK;
}

int REDirect::rd_scale(const float scale_factor[3])
{
	//cout << "rd_scale" << endl;

	scale_matrix(current_xform, scale_factor[0], scale_factor[1], scale_factor[2]);

	inv_scale_matrix(normal_xform, scale_factor[0], scale_factor[1], scale_factor[2]);

	return RD_OK;
}

int REDirect::rd_rotate_xy(float angle)
{
	//cout << "rd_rotate_xy" << endl;

	rotate_xy(current_xform, (double)angle);

	inv_rotate_xy(normal_xform, (double)angle);

	return RD_OK;
}

int REDirect::rd_rotate_yz(float angle)
{
	//cout << "rd_rotate_yz" << endl;

	rotate_yz(current_xform, (double)angle);

	inv_rotate_yz(normal_xform, (double)angle);

	return RD_OK;
}

int REDirect::rd_rotate_zx(float angle)
{
	//cout << "rd_rotate_zx" << endl;

	rotate_zx(current_xform, (double)angle);

	inv_rotate_zx(normal_xform, (double)angle);

	return RD_OK;
}

int REDirect::rd_camera_eye(const float eyepoint[3])
{
	//cout << "rd_camera_eye" << endl;

	Point new_eye(eyepoint[0], eyepoint[1], eyepoint[2]);

	cam_eye = new_eye;	

	return RD_OK;
}

int REDirect::rd_camera_at(const float atpoint[3])
{
	//cout << "rd_camera_at" << endl;

	Point new_at(atpoint[0], atpoint[1], atpoint[2]);

	cam_at = new_at;
	
	return RD_OK;
}

int REDirect::rd_camera_up(const float up[3])
{
	//cout << "rd_camera_up" << endl;

	Vector3 new_up(up[0], up[1], up[2]);

	cam_up = new_up;

	return RD_OK;
}

int REDirect::rd_camera_fov(float fov)
{
	//cout << "rd_camera_fov" << endl;

	cam_fov = (double)fov;

	return RD_OK;
}

int REDirect::rd_clipping(float znear, float zfar)
{
	//cout << "rd_camera_clipping" << endl;

	cam_near = (double)znear;
	
	cam_far = (double)zfar;
	
	return RD_OK;
}

int REDirect::rd_pointset(const string & vertex_type, int nvertex, const float * vertex)
{
	point_set(nvertex, vertex);

	return RD_OK;
}

int REDirect::rd_polyset(const string & vertex_type, int nvertex, const float * vertex, int nface, const int * face)
{
	polygon_set(vertex, nface, face);

	return RD_OK;
}

int REDirect::rd_xform_push(void)
{
	//cout << "rd_xform_push" << endl;

	xform_stack.push(current_xform);

	xform_stack.push(normal_xform);

	return RD_OK;
}

int REDirect::rd_xform_pop(void)
{
	//cout << "rd_xform_pop" << endl;

	normal_xform = xform_stack.top();

	xform_stack.pop();

	current_xform = xform_stack.top();

	xform_stack.pop();

	return RD_OK;
}

int REDirect::rd_cone(float height, float radius, float thetamax)
{
	//cout << "rd_cone" << endl;

	cone(height, radius, thetamax);

	return RD_OK;
}

int REDirect::rd_cube(void)
{
	//cout << "rd_cube" << endl;

	cube();
	
	return RD_OK;
}

int REDirect::rd_cylinder(float radius, float zmin, float zmax, float thetamax)
{
	cylinder(radius, zmin, zmax, thetamax);

	return RD_OK;
}

int REDirect::rd_disk(float height, float radius, float theta)
{
	disk(height, radius, theta);

	return RD_OK;
}

int REDirect::rd_sphere(float radius, float zmin, float zmax, float thetamax)
{
	sphere(radius, zmin, zmax, thetamax);

	return RD_OK;
}

int REDirect::rd_render_cleanup(void)
{
	z_buffer_cleanup();

	edge_table_cleanup();

	return RD_OK;
}

int REDirect::rd_opacity(float opacity)
{
	return RD_OK;
}

int REDirect::rd_emission(const float color[], float intensity)
{
	return RD_OK;
}

int REDirect::rd_surface(const string & shader_type)
{
	if (shader_type == "metal")
		surface_shader = metal;
	else if (shader_type == "plastic")
		surface_shader = plastic;
	else
		surface_shader = matte;

	return RD_OK;
}

int REDirect::rd_cone_light(const float pos[3], const float at[3], float theta_min, float theta_max, const float color[], float intensity)
{
	return RD_OK;
}

int REDirect::rd_point_light(const float pos[3], const float color[], float intensity)
{
	LightP temp(pos, color, intensity);

	point_l.push_back(temp);

	return RD_OK;
}

int REDirect::rd_far_light(const float dir[3], const float color[], float intensity)
{
	float rev_dir[3];

	for (int i = 0; i < 3; i++)
		rev_dir[i] = -dir[i];
	
	LightF temp(rev_dir, color, intensity);

	far_l.push_back(temp);

	return RD_OK;
}

int REDirect::rd_ambient_light(const float color[], float intensity)
{
	LightA temp(color, intensity);

	for (int i = 0; i < 3; i++)
		ambient_l[i] = temp[i];

	return RD_OK;
}

//ask about this
int REDirect::rd_specular_color(const float color[], int exponent)
{
	for (int i = 0; i < 3; i++)
		specular_color[i] = color[i];

	specular_exponent = exponent;

	return RD_OK;
}

int REDirect::rd_k_ambient(float Ka)
{
	ambient_k = Ka;

	return RD_OK;
}

int REDirect::rd_k_diffuse(float Kd)
{
	diffuse_k = Kd;

	return RD_OK;
}

int REDirect::rd_k_emission(float Ke)
{
	return RD_OK;
}

int REDirect::rd_k_specular(float Ks)
{
	specular_k = Ks;

	return RD_OK;
}

int REDirect::rd_attribute_push(void)
{
	return RD_OK;
}

int REDirect::rd_attribute_pop(void)
{
	return RD_OK;
}

int REDirect::rd_option_bool(const string & name, bool flag)
{
	if (name == "Interpolate")
		interpolation_flag = flag;

	return RD_OK;
}