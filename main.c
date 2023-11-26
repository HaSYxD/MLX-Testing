#include "fdf.h"
#include "draw_line.h"

void	draw_background(t_data *data)
{
	for (int j = 0; j < 1080; j++)
		for (int i = 0; i < 1920; i++)
			put_pixel_to_image(&data->img, i, j, 0x00000000);
}

int	handle_no_event(t_data *data)
{
	int	x;
	int	y;
	int	x1;
	int	y1;
	
	t_point	pnt[8];
	int	n = 0;
	for (int k = 0; k < 2; k++)
	{
		for (int j = 4; j < 6; j++)
		{
			for (int i = 8; i < 10; i++)
			{
				pnt[n].x = i * 150;
				pnt[n].z = j * 150;
				pnt[n].y = k * 150;
				n++;
			}
		}
	}
	float t = 0.1;
	draw_background(data);
	for (int i = 0; i < 8; i++)
	{
		x = pnt[i].x * cos(data->p) + pnt[i].y * sin(data->p);
		y = (pnt[i].x * sin(data->p) + pnt[i].y * cos(data->p)) * sin(t) + pnt[i].z * cos(t);
		x1 = pnt[i + 1].x * cos(data->p) + pnt[i + 1].y * sin(data->p);
		y1 = (pnt[i + 1].x * sin(data->p) + pnt[i + 1].y * cos(data->p)) * sin(t) + pnt[i + 1].z * cos(t);
		 if ((x >= 0 && y >= 0 && x <= 1920 && y <= 1080) && (x1 >= 0 && y1 >= 0 && x1 <= 1920 && y1 <= 1080))
			draw_line(&data->img, x, y, x1, y1, 0x00FF0000);
		//put_pixel_to_image(&data->img, x, y, 0x00FF0000);
	}
	
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
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1920, 1080, "Hello World!");
	
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, 1920, 1080);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	data.p = 0;
	/*t_point	pnt[81];
	int	n = 0;
	for (int j = 3; j < 12; j++)
	{
		for (int i = 3; i < 12; i++)
		{
			pnt[n].x = i * 50;
			pnt[n].z = j * 50;
			pnt[n].y = 0;
			n++;
		}
	}
	
	float t = 1;
	
	for (int i = 0; i < 81; i++)
	{
		x = pnt[i].x * cos(p) + pnt[i].y * sin(p);
		y = (pnt[i].x * sin(p) + pnt[i].y * cos(p)) * sin(t) + pnt[i].z * cos(t);
		x1 = pnt[i + 1].x * cos(p) + pnt[i + 1].y * sin(p);
		y1 = (pnt[i + 1].x * sin(p) + pnt[i + 1].y * cos(p)) * sin(t) + pnt[i + 1].z * cos(t);
		if (x >= 0 && y >= 0 && x <= 1920 && y <= 1080)
			draw_line(&data.img, x, y, x1, y1, 0x00FF0000);
		//put_pixel_to_image(&data.img, x, y, 0x00FF0000);
	}*/
	/*
	for (int j = 0; j < 25; j++)
	{
		for (int i = 0; i < 25; i++)
		{
			if (i >= 0 && j >= 0)
			{
				draw_line(&data.img, i * 25, j * 25, (i + 1) * 25, j * 25, 0x00FF0000);
				draw_line(&data.img, i * 25, j * 25, i * 25, (j + 1) * 25, 0x00FF0000);
				draw_line(&data.img, i * 25, (j + 1) * 25, (i + 1) * 25, j * 25, 0x00FF0000);
			}
		}
	}*/
	
	
	//draw_line(&data.img, 5, 5, 150, 200, 0x00FF0000);
	//draw_line(&data.img, 150, 200, 200, 50, 0x00FF0000);
	
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);

	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_input, &data);

	mlx_loop(data.mlx_ptr);

	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
