/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:46:35 by aliaudet          #+#    #+#             */
/*   Updated: 2023/12/07 14:46:38 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "matrices.h"
#include "draw.h"

static int	check_incr(int n1, int n2)
{
	if (n1 > n2)
		return (-1);
	return (1);
}

static void	first_case(t_data *data, t_vect2D p1, t_vect2D p2, t_color color)
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
		put_pixel_to_image(data, p1.x, p1.y, color);
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

static void	second_case(t_data *data, t_vect2D p1, t_vect2D p2, t_color color)
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
		put_pixel_to_image(data, p1.x, p1.y, color);
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

void	put_pixel_to_image(t_data *data, int x, int y, t_color color)
{
	char	*pixel;
	int		f_col;

	if (x >= 0 && y >= 0 && x <= WIN_WIDTH && y <= WIN_HEIGHT)
	{
		pixel = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
		f_col = color.r << 16 | color.g << 8 | color.b;
		*(int *)pixel = f_col;
	}
}

void	draw_line(t_data *data, t_vect2D p1, t_vect2D p2, t_color color)
{
	if (abs((int)p2.x - (int)p1.x) > abs((int)p2.y - (int)p1.y))
		first_case(data, p1, p2, color);
	else if (abs((int)p2.x - (int)p1.x) <= abs((int)p2.y - (int)p1.y))
		second_case(data, p1, p2, color);
}
