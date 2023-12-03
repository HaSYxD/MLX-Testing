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

#include "fdf.h"
#include "matrices.h"
#include "renderer.h"
#include "draw_line.h"
#include "get_next_line.h"
#include "file_handling.h"
#include "utils.h"

void	close_app(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->obj_dt.vertex);
	free(data->vert_buff);
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

void	draw_background(t_data *data)
{
	for (int j = 0; j < WIN_HEIGHT; j++)
		for (int i = WIN_WIDTH / 5; i < (WIN_WIDTH / 5) * 4; i++)
			put_pixel_to_image(&data->img, i, j, 0x00000000);
}

int	handle_no_event(t_data *data)
{
	t_vect2D	*sc;
	
	data->obj_dt.angle.x += 0.001;
	data->obj_dt.angle.y += 0.001;
	data->obj_dt.angle.z += 0.001;
	sc = from_3dto_2d(data);
	draw_background(data);
	for (int i = 0; i < data->obj_dt.num_vert - 1; i++)
	{
		//put_pixel_to_image(&data->img, sc[i].x, sc[i].y, 0x00FF0000);
		if (sc[i].x >= 0 &&  sc[i].y >= 0 && sc[i].x <= WIN_WIDTH
			&& sc[i].y <= WIN_HEIGHT
			&& (i % (data->obj_dt.map_width)) != (data->obj_dt.map_width - 1)
			&& i + data->obj_dt.map_width < data->obj_dt.num_vert
			&& sc[i + data->obj_dt.map_width].y != 0)
		{
			draw_line(&data->img, sc[i], sc[i + data->obj_dt.map_width], 0x00FF0000);
			draw_line(&data->img, sc[i], sc[i + 1], 0x00FF0000);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	free(sc);
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_app(data);
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
	data.obj_dt.angle = (t_vect3D){ISO_X_ANGLE, ISO_Y_ANGLE, ISO_Z_ANGLE};
	data.vert_buff = malloc(sizeof(t_vect3D) * data.obj_dt.num_vert);
	if (data.converted)
		mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_input, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
