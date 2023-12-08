#include "utils.h"
#include "fdf.h"
#include "get_next_line.h"
#include "file_handling.h"
#include <stdio.h>

void	convert_ind(t_data *data, char *raw, t_count c)
{
	if (c.j == 1)
		data->obj.index[c.i].x = (ft_atoi(raw)) -1;
	if (c.j == 2)
		data->obj.index[c.i].y = (ft_atoi(raw)) -1;
	if (c.j == 3)
		data->obj.index[c.i].z = (ft_atoi(raw)) -1;
}

void	convert_obj_ind(t_data *data, char *raw)
{
	t_count	c;

	c = (t_count){0, 0, 0};
	while (*raw && *raw != 'f')
		raw++;
	while (*raw && c.i < data->obj.num_ind)
	{
		if ((*raw != ' ' && *raw != '\n' && *raw != 'f' && *raw != '/') && c.k == 0)
		{
			c.k = 1;
			convert_ind(data, raw, c);
		}
		else if (*raw == ' ' || *raw == '\n' || *raw == 'f')
			c.k = 0;
		if (*raw == ' ')
			c.j++;
		if (*raw == '\n')
		{
			c.i++;
			c.j = 0;
		}
		raw++;
	}
	printf("%s", raw);
}

void	convert_coord(t_data *data, char *raw, t_count c)
{
	if (c.j == 1)
		data->obj.vertex[c.i].x = (ft_atoi(raw)) / 1000000.000000;
	if (c.j == 2)
		data->obj.vertex[c.i].y = (ft_atoi(raw)) / 1000000.000000;
	if (c.j == 3)
		data->obj.vertex[c.i].z = (ft_atoi(raw)) / 1000000.000000;
}

void	convert_obj_vert(t_data *data, char *raw)
{
	t_count	c;

	c = (t_count){0, 0, 0};
	while (*raw && c.i < data->obj.num_vert)
	{
		if ((*raw != ' ' && *raw != '\n' && *raw != 'v' && *raw != '.') && c.k == 0)
		{
			c.k = 1;
			convert_coord(data, raw, c);
		}
		else if (*raw == ' ' || *raw == '\n' || *raw == 'v')
			c.k = 0;
		if (*raw == ' ')
			c.j++;
		if (*raw == '\n')
		{
			c.i++;
			c.j = 0;
		}
		raw++;
	}
	convert_obj_ind(data, raw);
	normalise_data(data);
}

int	handle_obj(char *argv[], t_data *data)
{
	static char	*raw;
	char		*buff;
	int			fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	data->obj.num_vert = 0;
	while (get_next_line(fd, &buff) && *buff != '\0')
	{
		if ((buff[0] == 'v' && buff[1] == ' ') || (buff[0] == 'f' && buff[1] == ' '))
			raw = ft_strjoin(raw, buff);
		if (buff[0] == 'v' && buff[1] == ' ')
			data->obj.num_vert++;
		if (buff[0] == 'f' && buff[1] == ' ')
			data->obj.num_ind++;
		free(buff);
	}
	data->obj.vertex = malloc(sizeof(t_vect3D) * data->obj.num_vert);
	data->obj.index = malloc(sizeof(t_vect3D) * data->obj.num_ind);
	convert_obj_vert(data, raw);
	free(raw);
	free(buff);
	close(fd);
	return (0);
}