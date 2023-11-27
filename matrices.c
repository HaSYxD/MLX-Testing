#include "fdf.h"
#include "matrices.h"

t_vect2D    matrix_mul2D(t_vect3D coords, t_vect3D *mat)
{
    t_vect2D    sc;

    sc.x = (coords.x * mat[0].x) + (coords.y * mat[0].y) + (coords.z * mat[0].z);
    sc.y = (coords.x * mat[1].x) + (coords.y * mat[1].y) + (coords.z * mat[1].z);
    return (sc);
}