/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:49:06 by aliaudet          #+#    #+#             */
/*   Updated: 2023/12/07 14:49:08 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include "matrices.h"
# include "mlx.h"

# ifndef SCALE
#  define SCALE	200
# endif

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define MLX_ERROR	-1

# define ISO_X_ANGLE	0.785993
# define ISO_Y_ANGLE	-0.615996
# define ISO_Z_ANGLE	0.523997

typedef struct s_count
{
	int	i;
	int	j;
	int	k;
}	t_count;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_object
{
	t_vect3D	*vertex;
	t_vect3D	angle;
	int			width;
	int			depth;
	int			num_vert;
}	t_object;

typedef struct s_data
{
	t_object	obj;
	t_vect3D	*v_buff;
	t_vect3D	cam_pos;
	t_img		img;
	void		*mlx_ptr;
	void		*win_ptr;
	int			file_state;
	int			converted;
	int			tick;
}	t_data;

#endif
