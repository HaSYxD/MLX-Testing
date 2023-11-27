#include "fdf.h"
#include "matrices.h"
#include "renderer.h"

t_vect3D	rotate_point_x(t_vect3D obj, float angle)
{
	t_matrix3D	rot_matrix_x;

	rot_matrix_x = (t_matrix3D){
		(t_vect3D){1, 0, 0},
		(t_vect3D){0, cos(angle), -sin(angle)},
		(t_vect3D){0, sin(angle), cos(angle)}
	};
	obj = matrix_mul3D(obj, rot_matrix_x);
	return (obj);
}

t_vect3D	rotate_point_y(t_vect3D obj, float angle)
{
	t_matrix3D	rot_matrix_y;

	rot_matrix_y = (t_matrix3D){
		(t_vect3D){cos(angle), 0, -sin(angle)},
		(t_vect3D){0, 1, 0},
		(t_vect3D){-sin(angle), 0, cos(angle)}
	};
	obj = matrix_mul3D(obj, rot_matrix_y);
	return (obj);
}

t_vect3D	rotate_point_z(t_vect3D obj, float angle)
{
	t_matrix3D	rot_matrix_z;

	rot_matrix_z = (t_matrix3D){
		(t_vect3D){cos(angle), -sin(angle), 0},
		(t_vect3D){sin(angle), cos(angle), 0},
		(t_vect3D){0, 0, 1}
	};
	obj = matrix_mul3D(obj, rot_matrix_z);
	return (obj);
}
