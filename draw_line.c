#include "fdf.h"
#include "matrices.h"
#include "draw_line.h"

static int	check_incr(int n1, int n2)
{
	if (n1 > n2)
		return (-1);
	return (1);
}

static void	first_case(t_img *img, t_vect2D p1, t_vect2D p2, int color)
{
	int	e;
	int	i;
	int	dx;
	int	dy;
	
	i = 0;
	e = abs((int)p2.x - (int)p1.x);
	dx = e;
	dy = 2 * abs((int)p2.y - (int)p1.y);
	while (i <= dx)
	{
		put_pixel_to_image(img, p1.x, p1.y, color);
		i++;
		p1.x += check_incr(p1.x, p2.x);
		e -= dy;
		if (e < 0)
		{
			p1.y += check_incr(p1.y, p2.y);
			e += dx * 2;
		}
	}
}

static void	second_case(t_img *img, t_vect2D p1, t_vect2D p2, int color)
{
	int	e;
	int	i;
	int	dx;
	int	dy;
	
	i = 0;
	e = abs((int)p2.y - (int)p1.y);
	dx = 2 * abs((int)p2.x - (int)p1.x);
	dy = e;
	while (i <= dy)
	{
		put_pixel_to_image(img, p1.x, p1.y, color);
		i++;
		p1.y += check_incr(p1.y, p2.y);
		e -= dx;
		if (e < 0)
		{
			p1.x += check_incr(p1.x, p2.x);
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

void	draw_line(t_img *img, t_vect2D p1, t_vect2D p2, int color)
{
	if (abs((int)p2.x - (int)p1.x) > abs((int)p2.y - (int)p1.y))
		first_case(img, p1, p2, color);
	else if (abs((int)p2.x - (int)p1.x) <= abs((int)p2.y - (int)p1.y))
		second_case(img, p1, p2, color);
}