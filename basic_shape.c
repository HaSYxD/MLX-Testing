/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 00:22:09 by aliaudet          #+#    #+#             */
/*   Updated: 2023/11/21 01:31:38 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_shape.h"
#include <stdio.h>

void    put_pixel(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void    draw_rect(t_data *data, int x, int y, int width, int height, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (y + height))
	{
		while (j < (x + width))
		{
			put_pixel(data, x + j, y + i, color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_circle(t_data *data, int x, int y, int radius, int color)
{
	int	i;
	int	j;

	i = y - radius;
	j = x - radius;
	while (i < (y + radius))
	{
		while (j < (x + radius))
		{
			if (pow(j - x, 2) + pow(i - y, 2) < pow(radius, 2))
				put_pixel(data, j, i, color);
			j++;
		}
		j = x - radius;
		i++;
	}
}
