#include "fdf.h"
#include "matrices.h"
#include "renderer.h"

t_vect3D	*rotate_x(t_vect3D *obj, float angle, int num_vert)
{
	t_matrix3D	rot_matrix_x;
	int			i;

	i = 0;
	rot_matrix_x = (t_matrix3D){
		(t_vect3D){1, 0, 0},
		(t_vect3D){0, cos(angle), -sin(angle)},
		(t_vect3D){0, sin(angle), cos(angle)}
	};
	while (i < num_vert)
	{
		obj[i] = matrix_mul3D(obj[i], rot_matrix_x);
		i++;
	}
	return (obj);
}

t_vect3D	*rotate_y(t_vect3D *obj, float angle, int num_vert)
{
	t_matrix3D	rot_matrix_y;
	int			i;

	i = 0;
	rot_matrix_y = (t_matrix3D){
		(t_vect3D){cos(angle), 0, -sin(angle)},
		(t_vect3D){0, 1, 0},
		(t_vect3D){-sin(angle), 0, cos(angle)}
	};
	while (i < num_vert)
	{
		obj[i] = matrix_mul3D(obj[i], rot_matrix_y);
		i++;
	}
	return (obj);
}

t_vect3D	*rotate_z(t_vect3D *obj, float angle, int num_vert)
{
	t_matrix3D	rot_matrix_z;
	int			i;

	i = 0;
	rot_matrix_z = (t_matrix3D){
		(t_vect3D){cos(angle), -sin(angle), 0},
		(t_vect3D){sin(angle), cos(angle), 0},
		(t_vect3D){0, 0, 1}
	};
	while (i < num_vert)
	{
		obj[i] = matrix_mul3D(obj[i], rot_matrix_z);
		i++;
	}
	return (obj);
}

t_vect2D	*project_ortho(t_vect3D	*vert_buff, int num_vert)
{
	t_matrix3D	proj_matrix;
	t_vect2D	*projected_pnt;
	int			i;

	i = 0;
	proj_matrix = (t_matrix3D){
		(t_vect3D){1, 0, 0},
		(t_vect3D){0, 1, 0},
		(t_vect3D){0, 0, 0}
	};
	projected_pnt = malloc(sizeof(t_vect2D) * num_vert);
	while (i < num_vert)
	{
		projected_pnt[i] = matrix_mul2D(vert_buff[i], proj_matrix);
		projected_pnt[i].x *= SCALE;
		projected_pnt[i].y *= SCALE;
		projected_pnt[i].x += WIN_WIDTH / 2;
		projected_pnt[i].y += WIN_HEIGHT / 2;
		i++;
	}
	return (projected_pnt);
}

t_vect2D	*from_3dto_2d(t_data *data)
{
	t_vect3D	*vert_buff;
	t_vect2D	*projected_pnt;
	int			num_vert;
	int			i;

	i = 0;
	num_vert = data->map_data.map_width * data->map_data.map_depth;
	vert_buff = malloc(sizeof(t_vect3D) * num_vert);
	while (i < num_vert)
	{
		vert_buff[i] = data->map_data.map_coords[i];
		i++;
	}
	vert_buff = rotate_x(vert_buff, ISO_X_ANGLE, num_vert);
	vert_buff = rotate_y(vert_buff, ISO_Y_ANGLE, num_vert);
	vert_buff = rotate_z(vert_buff, ISO_Z_ANGLE, num_vert);
	projected_pnt = project_ortho(vert_buff, num_vert);
	free(vert_buff);
	return (projected_pnt);
}
