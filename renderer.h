#ifndef RENDERER_H
# define RENDERER_H

t_vect3D	*rotate_x(t_vect3D *obj, float angle, int num_vert);
t_vect3D	*rotate_y(t_vect3D *obj, float angle, int num_vert);
t_vect3D	*rotate_z(t_vect3D *obj, float angle, int num_vert);
t_vect2D	*project_ortho(t_vect3D	*vert_buff, int num_vert);
t_vect2D	*from_3dto_2d(t_data *data);

#endif