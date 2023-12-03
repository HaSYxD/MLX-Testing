#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>
# include <math.h>
# include "matrices.h"
# include "mlx.h"

# define PI	3.13149265359
# define WIN_WIDTH	1600
# define WIN_HEIGHT	900
# define SCALE	250
# define MLX_ERROR	-1

# define ISO_X_ANGLE	0.785993
# define ISO_Y_ANGLE	-0.615996
# define ISO_Z_ANGLE	0.523997

typedef struct	s_img
{
	void	*mlx_img;
	char	*addr;
	int	bpp;
	int	line_len;
	int	endian;
}	t_img;
/*
typedef struct s_map_data
{
	t_vect3D	*map_coords;
	t_vect3D	*index;
	t_vect3D	draw_angle;
	int	map_width;
	int	map_depth;
}	t_map_data;
*/
typedef struct s_object
{
	t_vect3D	*vertex;
	t_vect3D	*index;
	t_vect3D	angle;
	int	map_width;
	int	map_depth;
	int	num_vert;
}	t_object;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_vect3D	*vert_buff;
	t_object	obj_dt;
	int	converted;
}	t_data;

#endif