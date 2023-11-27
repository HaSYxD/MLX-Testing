#ifndef MATRICES
# define MATRICES

typedef struct s_vect2D
{
    float   x;
    float   y;
}   t_vect2D;

typedef struct s_vect3D
{
    float   x;
    float   y;
    float   z;
}   t_vect3D;

t_vect2D    matrix_mul2D(t_vect3D coords, t_vect3D *mat);

#endif