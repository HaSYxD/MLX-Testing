/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:54:05 by aliaudet          #+#    #+#             */
/*   Updated: 2023/12/07 14:54:07 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "matrices.h"
#include "renderer.h"

t_vect3D	*rotate_x(t_data *data, float angle)
{
	t_matrix3D	rot_matrix_x;
	int			i;

	i = 0;
	rot_matrix_x = (t_matrix3D){
		(t_vect3D){1, 0, 0},
		(t_vect3D){0, cos(angle), -sin(angle)},
		(t_vect3D){0, sin(angle), cos(angle)}
	};
	while (i < data->obj.num_vert)
	{
		data->v_buff[i] = matrix_mul3d(data->v_buff[i], rot_matrix_x);
		i++;
	}
	return (data->v_buff);
}

t_vect3D	*rotate_y(t_data *data, float angle)
{
	t_matrix3D	rot_matrix_y;
	int			i;

	i = 0;
	rot_matrix_y = (t_matrix3D){
		(t_vect3D){cos(angle), 0, -sin(angle)},
		(t_vect3D){0, 1, 0},
		(t_vect3D){-sin(angle), 0, cos(angle)}
	};
	while (i < data->obj.num_vert)
	{
		data->v_buff[i] = matrix_mul3d(data->v_buff[i], rot_matrix_y);
		i++;
	}
	return (data->v_buff);
}

t_vect3D	*rotate_z(t_data *data, float angle)
{
	t_matrix3D	rot_matrix_z;
	int			i;

	i = 0;
	rot_matrix_z = (t_matrix3D){
		(t_vect3D){cos(angle), -sin(angle), 0},
		(t_vect3D){sin(angle), cos(angle), 0},
		(t_vect3D){0, 0, 1}
	};
	while (i < data->obj.num_vert)
	{
		data->v_buff[i] = matrix_mul3d(data->v_buff[i], rot_matrix_z);
		i++;
	}
	return (data->v_buff);
}

t_vect2D	*project_ortho(t_data	*data)
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
	projected_pnt = malloc(sizeof(t_vect2D) * data->obj.num_vert);
	while (i < data->obj.num_vert)
	{
		projected_pnt[i] = matrix_mul2d(data->v_buff[i], proj_matrix);
		projected_pnt[i].x *= SCALE;
		projected_pnt[i].y *= SCALE;
		projected_pnt[i].x += (WIN_WIDTH / 2);
		projected_pnt[i].y += (WIN_HEIGHT / 2);
		i++;
	}
	return (projected_pnt);
}

t_vect2D	*from_3dto_2d(t_data *data)
{
	t_vect2D	*projected_pnt;
	int			i;

	i = 0;
	while (i < data->obj.num_vert)
	{
		data->v_buff[i] = data->obj.vertex[i];
		i++;
	}
	data->v_buff = rotate_x(data, data->obj.angle.x);
	data->v_buff = rotate_y(data, data->obj.angle.y);
	data->v_buff = rotate_z(data, data->obj.angle.z);
	projected_pnt = project_ortho(data);
	return (projected_pnt);
}
