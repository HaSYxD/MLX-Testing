#include "fdf.h"
#include "matrices.h"

t_vect2D	matrix_mul2D(t_vect3D coords, t_matrix3D mat)
{
	t_vect2D    sc;

	sc.x = (coords.x * mat.a.x) + (coords.y * mat.a.y) + (coords.z * mat.a.z);
	sc.y = (coords.x * mat.b.x) + (coords.y * mat.b.y) + (coords.z * mat.b.z);
	return (sc);
}

t_vect3D	matrix_mul3D(t_vect3D coords, t_matrix3D mat)
{
	t_vect3D    sc;

	sc.x = (coords.x * mat.a.x) + (coords.y * mat.a.y) + (coords.z * mat.a.z);
	sc.y = (coords.x * mat.b.x) + (coords.y * mat.b.y) + (coords.z * mat.b.z);
	sc.z = (coords.x * mat.c.x) + (coords.y * mat.c.y) + (coords.z * mat.c.z);
	return (sc);
}