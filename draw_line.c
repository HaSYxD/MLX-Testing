#include "fdf.h"
#include "draw_line.h"
static int	check_incr(int n1, int n2)
{
	if (n1 > n2)
		return (-1);
	return (1);
}

static void	first_case(t_img *img, int x1, int y1, int x2, int y2, int color)
{
	int	e;
	int	i;
	int	dx;
	int	dy;
	
	i = 0;
	e = abs(x2 - x1);
	dx = e;
	dy = 2 * abs(y2 - y1);
	while (i <= dx)
	{
		put_pixel_to_image(img, x1, y1, color);
		i++;
		x1 += check_incr(x1, x2);
		e -= dy;
		if (e < 0)
		{
			y1 += check_incr(y1, y2);
			e += dx * 2;
		}
	}
}

static void	second_case(t_img *img, int x1, int y1, int x2, int y2, int color)
{
	int	e;
	int	i;
	int	dx;
	int	dy;
	
	i = 0;
	e = abs(y2 - y1);
	dx = 2 * abs(x2 - x1);
	dy = e;
	while (i <= dy)
	{
		put_pixel_to_image(img, x1, y1, color);
		i++;
		y1 += check_incr(y1, y2);
		e -= dx;
		if (e < 0)
		{
			x1 += check_incr(x1, x2);
			e += dy * 2;
		}
	}
}

void	put_pixel_to_image(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	draw_line(t_img *img, int x1, int y1, int x2, int y2, int color)
{
	if (abs(x2 - x1) > abs(y2 - y1))
		first_case(img, x1, y1, x2, y2, color);
	else if (abs(x2 - x1) <= abs(y2 - y1))
		second_case(img, x1, y1, x2, y2, color);
}