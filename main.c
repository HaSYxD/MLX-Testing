#include "fdf.h"
#include "matrices.h"
#include "draw_line.h"

void	draw_background(t_data *data)
{
	for (int j = 0; j < WIN_HEIGHT; j++)
		for (int i = 0; i < WIN_WIDTH; i++)
			put_pixel_to_image(&data->img, i, j, 0x00000000);
}

int	handle_no_event(t_data *data)
{
	int	angle = data->p;
	t_vect2D	sc;
	t_vect3D	pnt[4];
	t_vect3D	proj_matrix[2] = {
		(t_vect3D){1, 0, 0},
		(t_vect3D){0, 1, 0}
	};
	t_vect3D	rot_matrixZ[2] = {
		(t_vect3D){cos(angle), -sin(angle), 0},
		(t_vect3D){sin(angle), cos(angle), 0}
	};
	t_vect3D	rot_matrixY[2] = {
		(t_vect3D){cos(angle), 0, -sin(angle)},
		(t_vect3D){0, 1, 0}
	};
	pnt[0] = (t_vect3D){605, 105, 10};
	pnt[1] = (t_vect3D){655, 105, 10};
	pnt[2] = (t_vect3D){655, 155, 10};
	pnt[3] = (t_vect3D){605, 155, 10};
	draw_background(data);

	for (int i = 0; i < 4; i++)
	{
		sc = matrix_mul2D(pnt[i], proj_matrix);
		sc = matrix_mul2D((t_vect3D){sc.x, sc.y, 0}, rot_matrixZ);
		sc = matrix_mul2D((t_vect3D){sc.x, sc.y, 0}, rot_matrixY);
		if (sc.x >= 0 && sc.y >= 0)
			put_pixel_to_image(&data->img, sc.x, sc.y, 0x00FF0000);
	}
	//float t = 0;
	/*for (int i = 0; i < 8; i++)
	{
		x = pnt[i].x * cos(data->p) + pnt[i].y * sin(data->p);
		y = (pnt[i].x * sin(data->p) + pnt[i].y * cos(data->p)) * sin(t) + pnt[i].z * cos(t);
		x1 = pnt[i + 1].x * cos(data->p) + pnt[i + 1].y * sin(data->p);
		y1 = (pnt[i + 1].x * sin(data->p) + pnt[i + 1].y * cos(data->p)) * sin(t) + pnt[i + 1].z * cos(t);
		if ((x >= 0 && y >= 0 && x <= WIN_WIDTH && y <= WIN_HEIGHT) && (x1 >= 0 && y1 >= 0 && x1 <= WIN_WIDTH && y1 <= WIN_HEIGHT))
			//draw_line(&data->img, x, y, x1, y1, 0x00FF0000);
			put_pixel_to_image(&data->img, x, y, 0x00FF0000);
	}*/
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (keysym == XK_d)
		data->p += 0.025;
	if (keysym == XK_a)
		data->p -= 0.025;

	return (0);
}

int	main(void)
{
	t_data	data;

	//int	x;
	//int	y;
	//int	x1;
	//int	y1;
	
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Hello World!");
	
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	data.p = 0;

	//mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);

	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_input, &data);

	mlx_loop(data.mlx_ptr);

	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
