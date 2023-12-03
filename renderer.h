#ifndef RENDERER_H
# define RENDERER_H

t_vect3D	*rotate_x(t_data *data, float angle);
t_vect3D	*rotate_y(t_data *data, float angle);
t_vect3D	*rotate_z(t_data *data, float angle);
t_vect2D	*project_ortho(t_data *data);
t_vect2D	*from_3dto_2d(t_data *data);

#endif