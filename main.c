#include "basic_shape.h"

int	main(void)
{
	void	*mlx;
	t_data	plane;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello World!");
	
	plane.img = mlx_new_image(mlx, 1920, 1080);
	plane.addr = mlx_get_data_addr(plane.img, &plane.bpp, &plane.line_length, &plane.endian);
	
	draw_rect(&plane, 5, 5, 100, 100, 0x00FF0000);
	draw_circle(&plane, 500, 500, 250, 0x0000FF00);
	mlx_put_image_to_window(mlx, mlx_win, plane.img, 0, 0);

	mlx_loop(mlx);
	return (0);
}
