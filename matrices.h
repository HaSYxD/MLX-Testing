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

t_vect2D	matrix_mul2D(t_vect3D coords, t_matrix3D mat);
t_vect3D	matrix_mul3D(t_vect3D coords, t_matrix3D mat);

#endif