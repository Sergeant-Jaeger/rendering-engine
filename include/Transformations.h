#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "XForm.h"
#include "Vector3.h"
#include "Point.h"

void translate_matrix(XForm &current, const double &tx, const double &ty, const double &tz);

void scale_matrix(XForm &current, const double &sx, const double &sy, const double &sz);

void rotate_xy(XForm &current, const double &theta);

void rotate_yz(XForm &current, const double &theta);

void rotate_zx(XForm &current, const double &theta);

void inv_translate_matrix(XForm &normal, const double &tx, const double &ty, const double &tz);

void inv_scale_matrix(XForm &normal, const double &sx, const double &sy, const double &sz);

void inv_rotate_xy(XForm &normal, const double &theta);

void inv_rotate_yz(XForm &normal, const double &theta);

void inv_rotate_zx(XForm &normal, const double &theta);

XForm world_to_camera(const Point &eye, const Point &at, const Vector3 &up);

XForm camera_to_clip(const double &fov, const double &near, const double &far, const double &aspect);

XForm clip_to_device(const int &width, const int &height);

#endif /*TRANSFORMATIONS_H*/