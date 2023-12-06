#ifndef DRAW_H
# define DRAW_H

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

void	draw_line(t_img *img, t_vect2D p1, t_vect2D p2, t_color color);
void	put_pixel_to_image(t_img *img, int x, int y, t_color color);
void	draw_background(t_data *data);
void	draw_fdf_lines(t_data *data, t_vect2D *sc);

#endif