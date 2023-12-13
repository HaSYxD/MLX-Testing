/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:47:38 by aliaudet          #+#    #+#             */
/*   Updated: 2023/12/07 14:47:41 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "draw.h"

void	draw_background(t_data *data)
{
	t_count	c;

	c = (t_count){0, 0, 0};
	while (c.j < WIN_HEIGHT)
	{
		while (c.i < WIN_WIDTH)
		{
			put_pixel_to_image(data, c.i, c.j, (t_color){0, 0, 0});
			c.i++;
		}
		c.i = 0;
		c.j++;
	}
}

t_color	get_color(t_data *data, int vc)
{
	t_color	color;
	
	if ((data->obj.vertex[vc].y + 2) >= 0)
		color = (t_color){255 * (data->obj.vertex[vc].y + 2), 0, 0};
	else
		color = (t_color){255 * 0, 0, 0};
	return (color);
}

void	draw_fdf_lines(t_data *data, t_vect2D *sc)
{
	t_count	c;
	t_color color;

	c = (t_count){0, 0, 0};
	while (c.k < data->obj.num_vert)
	{
		color = get_color(data, c.k);
		if (c.i > 0)
			draw_line(data, sc[c.k],
				sc[c.k - 1], color);
		if (c.j > 0)
			draw_line(data, sc[c.k],
				sc[c.k - data->obj.width], color);
		c.i++;
		if (c.i == data->obj.width)
		{
			c.i = 0;
			c.j++;
		}
		c.k++;
	}
}
