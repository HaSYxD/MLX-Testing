#include "fdf.h"
#include "matrices.h"
#include "renderer.h"
#include "draw_line.h"

void	draw_background(t_data *data)
{
	for (int j = 0; j < WIN_HEIGHT; j++)
		for (int i = 0; i < WIN_WIDTH; i++)
			put_pixel_to_image(&data->img, i, j, 0x00000000);
}
t_vect2D	sc[8];
t_vect3D	vert_buff[8];
t_matrix3D	proj_matrix = {
	(t_vect3D){1, 0, 0},
	(t_vect3D){0, 1, 0},
	(t_vect3D){0, 0, 0}
};

int	handle_no_event(t_data *data)
{
	draw_background(data);
	
	data->angle.x = 0.785993;
	data->angle.y = -0.615996;
	data->angle.z = 0.523997;

	for (int i = 0; i < 8; i++)
		vert_buff[i] = data->vert_array[i];
	for (int i = 0; i < 8; i++)
		vert_buff[i] = rotate_point_x(vert_buff[i], data->angle.x);
	for (int i = 0; i < 8; i++)
		vert_buff[i] = rotate_point_y(vert_buff[i], data->angle.y);
	for (int i = 0; i < 8; i++)
		vert_buff[i] = rotate_point_z(vert_buff[i], data->angle.z);
	for (int i = 0; i < 8; i++)
	{
		sc[i] = matrix_mul2D(vert_buff[i], proj_matrix);
		sc[i].x *= 250;
		sc[i].y *= 250;
		sc[i].x += WIN_WIDTH / 2;
		sc[i].y += WIN_HEIGHT / 2;
	}
	//for (int i = 0; i < 7; i++)
	//	printf("%f, %f\n", sc[i].x, sc[i].y);
	draw_line(&data->img, sc[0], sc[1], 0x00FF0000);
	draw_line(&data->img, sc[1], sc[2], 0x00FF0000);
	draw_line(&data->img, sc[2], sc[3], 0x00FF0000);
	draw_line(&data->img, sc[3], sc[0], 0x00FF0000);
	
	draw_line(&data->img, sc[4], sc[5], 0x00FF0000);
	draw_line(&data->img, sc[5], sc[6], 0x00FF0000);
	draw_line(&data->img, sc[6], sc[7], 0x00FF0000);
	draw_line(&data->img, sc[7], sc[4], 0x00FF0000);
	
	draw_line(&data->img, sc[0], sc[4], 0x00FF0000);
	draw_line(&data->img, sc[1], sc[5], 0x00FF0000);
	draw_line(&data->img, sc[2], sc[6], 0x00FF0000);
	draw_line(&data->img, sc[3], sc[7], 0x00FF0000);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (keysym == XK_x)
		printf("%f, %f, %f\n", data->angle.x, data->angle.y, data->angle.z);

	return (0);
}

int	main(void)
{
	t_data	data;
	
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Hello World!");
	
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	int	map_line_len;
	int	map_line_count;
	int	i;
	char	*map_data = "012343210\n012343210\n012343210\n012343210\n012343210\n";
	
	i = 0;
	map_line_len = 0;
	map_line_count = 0;
	while (map_data[map_line_len] != '\n')
		map_line_len++;
	while (map_data[i])
	{
		if (map_data[i] == '\n')
			map_line_count++;
		i++;
	}
	int	j = 0;
	int	k = 0;
	float	vert_spacing = 2 / map_line_len;
	float	hor_spacing = 2 / map_line_count;
	while (map_data[j])
	{
		
	}
	
	/*data.vert_array = malloc(sizeof(t_vect3D) * 8);
	data.vert_array[0] = (t_vect3D){-1, 1, 1};
	data.vert_array[1] = (t_vect3D){1, 1, 1};
	data.vert_array[2] = (t_vect3D){1, -1, 1};
	data.vert_array[3] = (t_vect3D){-1, -1, 1};
	data.vert_array[4] = (t_vect3D){-1, 1, -1};
	data.vert_array[5] = (t_vect3D){1, 1, -1};
	data.vert_array[6] = (t_vect3D){1, -1, -1};
	data.vert_array[7] = (t_vect3D){-1, -1, -1};*/
	
	
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_input, &data);

	mlx_loop(data.mlx_ptr);
	
	mlx_destroy_image(data.mlx_ptr, &data.img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
