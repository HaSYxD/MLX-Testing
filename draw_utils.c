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
			put_pixel_to_image(&data->img, c.i, c.j, (t_color){153, 204, 255});
			c.i++;
		}
		c.i = 0;
		c.j++;
	}
}

void	draw_fdf_lines(t_data *data, t_vect2D *sc)
{
	t_count	c;

	c = (t_count){0, 0, 0};
	while (c.k < data->obj.num_vert)
	{
		if (c.i > 0)
			draw_line(&data->img, sc[c.k],
				sc[c.k - 1], (t_color){255, 255, 255});
		if (c.j > 0)
			draw_line(&data->img, sc[c.k],
				sc[c.k - data->obj.width], (t_color){255, 255, 255});
		c.i++;
		if (c.i == data->obj.width)
		{
			c.i = 0;
			c.j++;
		}
		c.k++;
	}
}
