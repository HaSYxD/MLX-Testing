/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:14:19 by aliaudet          #+#    #+#             */
/*   Updated: 2023/12/03 16:14:25 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "fdf.h"
#include "matrices.h"
#include "renderer.h"
#include "draw.h"
#include "file_handling.h"

void	close_app(t_data *data)
{
	if (data->win_ptr != NULL)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->img.mlx_img != NULL)
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	if (data->converted)
	{
		free(data->obj.vertex);
		free(data->v_buff);
	}
	free(data->mlx_ptr);
	exit(1);
}

int	init_app(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (MLX_ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	if (!data->win_ptr)
	{
		free(data->win_ptr);
		return (MLX_ERROR);
	}
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	return (0);
}

int	handle_no_event(t_data *data)
{
	t_vect2D	*sc;

	if (data->tick >= 1000)
	{
		sc = from_3dto_2d(data);
		draw_background(data);
		draw_fdf_lines(data, sc);
		mlx_put_image_to_window(data->mlx_ptr,
			data->win_ptr, data->img.mlx_img, 0, 0);
		free(sc);
		data->tick = 0;
	}
	data->tick++;
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_app(data);
	if (keysym == XK_Up)
		data->cam_pos.z += 5;
	if (keysym == XK_Down)
		data->cam_pos.z -= 5;
	if (keysym == XK_w)
		data->cam_pos.y += 2;
	if (keysym == XK_s)
		data->cam_pos.y -= 2;
	if (keysym == XK_q)
		data->obj.angle.x += 0.005;
	if (keysym == XK_e)
		data->obj.angle.x -= 0.005;
	if (keysym == XK_a)
		data->obj.angle.y += 0.005;
	if (keysym == XK_d)
		data->obj.angle.y -= 0.005;
	if (keysym == XK_z)
		data->obj.angle.z += 0.005;
	if (keysym == XK_c)
		data->obj.angle.z -= 0.005;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	data.converted = 0;
	if (init_app(&data) != 0)
		return (MLX_ERROR);
	if (check_user_input(argc, argv, &data) == -1)
		close_app(&data);
	data.obj.angle = (t_vect3D){ISO_X_ANGLE, ISO_Y_ANGLE, ISO_Z_ANGLE};
	data.cam_pos = (t_vect3D){WIN_WIDTH / 2, WIN_HEIGHT / 2, SCALE};
	data.v_buff = malloc(sizeof(t_vect3D) * data.obj.num_vert);
	data.tick = 0;
	if (data.converted)
		mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_input, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
