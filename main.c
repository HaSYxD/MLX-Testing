#include "fdf.h"
#include "matrices.h"
#include "renderer.h"
#include "draw_line.h"
#include "get_next_line.h"
#include "file_handling.h"

void	draw_background(t_data *data)
{
	for (int j = 0; j < WIN_HEIGHT; j++)
		for (int i = 0; i < WIN_WIDTH; i++)
			put_pixel_to_image(&data->img, i, j, 0x00000000);
}

int	render(t_data *data)
{
	t_vect2D	*sc;

	sc = from_3dto_2d(data);
	draw_background(data);
	for (int i = 0; i < 1600; i++)
	{
		if (sc[i].x >= 0 &&  sc[i].y >= 0 && sc[i].x <= WIN_WIDTH && sc[i].y <= WIN_HEIGHT
			&& (i % (data->map_data.map_width)) != (data->map_data.map_width - 1) && sc[i + data->map_data.map_width].y != 0)
		{
			draw_line(&data->img, sc[i], sc[i + data->map_data.map_width], 0x00FF0000);
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
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

int	main(int argc, char *argv[])
{
	if (check_user_input(argc, argv) == -1)
		return (-1);
	t_data	data;
	
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Hello World!");
	
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	data.map_data.map_width = 40;
	data.map_data.map_depth = 40;
	data.map_data.map_coords = malloc(sizeof(t_vect3D) * (data.map_data.map_width * data.map_data.map_depth));
	int k = 0;
	for (float i = -1; i < 1; i+=0.05)
	{
		for (float j = -1; j < 1; j+=0.05)
		{
			data.map_data.map_coords[k] = (t_vect3D){j, 0, i};
			k++;
		}
	}
	
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_input, &data);

	mlx_loop(data.mlx_ptr);

	free(data.map_data.map_coords);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
