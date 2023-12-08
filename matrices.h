/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:53:31 by aliaudet          #+#    #+#             */
/*   Updated: 2023/12/07 14:53:33 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRICES_H
# define MATRICES_H

typedef struct s_vect2D
{
	float	x;
	float	y;
}	t_vect2D;

typedef struct s_vect3D
{
	float	x;
	float	y;
	float	z;
}	t_vect3D;

typedef struct s_matrix3D
{
	t_vect3D	a;
	t_vect3D	b;
	t_vect3D	c;
}	t_matrix3D;

t_vect2D	matrix_mul2d(t_vect3D coords, t_matrix3D mat);
t_vect3D	matrix_mul3d(t_vect3D coords, t_matrix3D mat);

#endif
