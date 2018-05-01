#include "xforms.h"

void translate_matrix(XForm &current, const double &tx, const double &ty, const double &tz)
{
	XForm translate_xform;

	translate_xform.translate_matrix(tx, ty, tz);

	XForm translated_xform;

	translated_xform = current * translate_xform;

	current = translated_xform;
}

void scale_matrix(XForm &current, const double &sx, const double &sy, const double &sz)
{
	XForm scale_xform;

	scale_xform.scale_matrix(sx, sy, sz);

	XForm scaled_xform;

	scaled_xform = current * scale_xform;

	current = scaled_xform;
}

void rotate_xy(XForm &current, const double &theta)
{
	XForm rotate_xform;

	rotate_xform.rotate_xy_matrix(theta);

	XForm rotated_xform;

	rotated_xform = current * rotate_xform;

	current = rotated_xform;
}

void rotate_yz(XForm &current, const double &theta)
{
	XForm rotate_xform;

	rotate_xform.rotate_yz_matrix(theta);

	XForm rotated_xform;

	rotated_xform = current * rotate_xform;

	current = rotated_xform;
}

void rotate_zx(XForm &current, const double &theta)
{
	XForm rotate_xform;

	rotate_xform.rotate_zx_matrix(theta);

	XForm rotated_xform;

	rotated_xform = current * rotate_xform;

	current = rotated_xform;
}

void inv_translate_matrix(XForm &normal, const double &tx, const double &ty, const double &tz)
{
	XForm inv_translate_xform;

	inv_translate_xform.inv_translate_matrix(tx, ty, tz);

	inv_translate_xform.transpose_matrix();

	XForm inv_translated_xform;

	inv_translated_xform = normal * inv_translate_xform;

	normal = inv_translated_xform;
}

void inv_scale_matrix(XForm &normal, const double &sx, const double &sy, const double &sz)
{
	XForm inv_scale_xform;

	inv_scale_xform.inv_scale_matrix(sx, sy, sz);

	inv_scale_xform.transpose_matrix();

	XForm inv_scaled_xform;

	inv_scaled_xform = normal * inv_scale_xform;

	normal = inv_scaled_xform;
}

void inv_rotate_xy(XForm &normal, const double &theta)
{
	XForm inv_rotate_xform;

	inv_rotate_xform.inv_rotate_xy_matrix(theta);

	inv_rotate_xform.transpose_matrix();

	XForm inv_rotated_xform;

	inv_rotated_xform = normal * inv_rotate_xform;

	normal = inv_rotated_xform;
}

void inv_rotate_yz(XForm &normal, const double &theta)
{
	XForm inv_rotate_xform;

	inv_rotate_xform.inv_rotate_yz_matrix(theta);

	inv_rotate_xform.transpose_matrix();

	XForm inv_rotated_xform;

	inv_rotated_xform = normal * inv_rotate_xform;

	normal = inv_rotated_xform;
}

void inv_rotate_zx(XForm &normal, const double &theta)
{
	XForm inv_rotate_xform;

	inv_rotate_xform.inv_rotate_zx_matrix(theta);

	inv_rotate_xform.transpose_matrix();

	XForm inv_rotated_xform;

	inv_rotated_xform = normal * inv_rotate_xform;

	normal = inv_rotated_xform;
}

XForm world_to_camera(const Point &eye, const Point &at, const Vector &up)
{
	XForm eye_xform;

	eye_xform.eye_matrix(eye);

	Vector a;

	a = at - eye;

	a.normalize();

	Vector v;

	v = a.cross_product(up);

	v.normalize();

	Vector u;

	u = v.cross_product(a);

	u.normalize();

	XForm uva_xform;

	uva_xform.vua_matrix(v, u, a);

	XForm world_camera_xform;

	world_camera_xform = uva_xform * eye_xform;

	return world_camera_xform;
}

XForm camera_to_clip(const double &fov, const double &near, const double &far, const double &aspect)
{
	XForm camera_xform;

	camera_xform.camera_matrix(fov, near, far, aspect);

	return camera_xform;
}

XForm clip_to_device(const int &width, const int &height)
{
	XForm clip_xform;

	clip_xform.clip_matrix(width, height);

	return clip_xform;
}