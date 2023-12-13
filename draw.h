/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:47:08 by aliaudet          #+#    #+#             */
/*   Updated: 2023/12/07 14:47:11 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

void	draw_line(t_data *data, t_vect2D p1, t_vect2D p2, t_color color);
void	put_pixel_to_image(t_data *data, int x, int y, t_color color);
void	draw_background(t_data *data);
void	draw_fdf_lines(t_data *data, t_vect2D *sc);

#endif
