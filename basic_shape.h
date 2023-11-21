/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_shape.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 00:22:30 by aliaudet          #+#    #+#             */
/*   Updated: 2023/11/21 00:53:49 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIC_SHAPE_H
# define BASIC_SHAPE_H

#include <mlx.h>
#include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int	bpp;
	int	line_length;
	int	endian;
}	t_data;

void	put_pixel(t_data *data, int x, int y, int color);

void	draw_rect(t_data *data, int x, int y, int width, int height, int color);
void	draw_circle(t_data *data, int x, int y, int radius, int color);

#endif
