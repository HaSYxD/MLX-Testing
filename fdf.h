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

typedef struct	s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct	s_img
{
	void	*mlx_img;
	char	*addr;
	int	bpp;
	int	line_len;
	int	endian;
}	t_img;

typedef struct s_map_data
{
	t_vect3D	*map_coords;
	int	map_width;
	int	map_depth;
}	t_map_data;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_vect3D	*vert_array;
	t_vect3D	angle;
}	t_data;

#endif