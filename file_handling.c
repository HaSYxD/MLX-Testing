#include "utils.h"
#include "fdf.h"
#include "get_next_line.h"
#include "file_handling.h"

t_vect2D	get_min_max(t_data *data)
{
	t_vect2D	mm;
	int			i;

	i = 0;
	mm = (t_vect2D){0, 0};
	while (i < data->obj.num_vert)
	{
		if (mm.x > data->obj.vertex[i].x)
			mm.x = data->obj.vertex[i].x;
		if (mm.x > data->obj.vertex[i].y)
			mm.x = data->obj.vertex[i].y;
		if (mm.x > data->obj.vertex[i].z)
			mm.x = data->obj.vertex[i].z;
		if (mm.y < data->obj.vertex[i].x)
			mm.y = data->obj.vertex[i].x;
		if (mm.y < data->obj.vertex[i].y)
			mm.y = data->obj.vertex[i].y;
		if (mm.y < data->obj.vertex[i].z)
			mm.y = data->obj.vertex[i].z;
		i++;
	}
	return (mm);
}

void	normalise_data(t_data *data)
{
	t_vect2D	mm;
	int			i;

	i = 0;
	mm = get_min_max(data);
	if (mm.x < 0)
	{
		mm.y += abs(mm.x);
		mm.x += abs(mm.x);
	}
	while (i < data->obj.num_vert)
	{
		data->obj.vertex[i].x = (2 * ((data->obj.vertex[i].x - mm.x)
					/ (mm.y - mm.x)) - 1);
		data->obj.vertex[i].y = (2 * ((data->obj.vertex[i].y - mm.x)
					/ (mm.y - mm.x)) - 1) * -1;
		data->obj.vertex[i].z = (2 * ((data->obj.vertex[i].z - mm.x)
					/ (mm.y - mm.x)) - 1) * -1;
		i++;
	}
	data->converted = 1;
}

void	convert_fdf_data(t_data *data, char *raw)
{
	t_count	c;
	int		trigger;

	c = (t_count){0, 0, 0};
	trigger = 0;
	while (*raw && c.k < data->obj.num_vert)
	{
		if ((*raw != ' ' && *raw != '\n') && trigger == 0)
		{
			trigger = 1;
			data->obj.vertex[c.k] = (t_vect3D){c.i, ft_atoi(raw), c.j};
			c.i++;
			c.k++;
		}
		else if ((*raw == ' ' || *raw == '\n'))
			trigger = 0;
		if (*raw == '\n')
		{
			c.i = 0;
			c.j++;
		}
		raw++;
	}
	normalise_data(data);
}

int	handle_fdf(char *argv[], t_data *data)
{
	static char	*raw;
	char		*buff;
	int			width_check;
	int			fd;

	width_check = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	data->obj.depth = 0;
	while (get_next_line(fd, &buff) && *buff != '\0')
	{
		data->obj.width = countw(buff);
		raw = ft_strjoin(raw, buff);
		data->obj.depth++;
		free(buff);
	}
	data->obj.num_vert = data->obj.depth * data->obj.width;
	data->obj.vertex = malloc(sizeof(t_vect3D) * data->obj.num_vert);
	convert_fdf_data(data, raw);
	free(raw);
	close(fd);
	return (0);
}

int	check_user_input(int argc, char *argv[], t_data *data)
{
	if (argc < 2)
	{
		ft_putstr("Please input a file\n");
		return (-1);
	}
	if (argc > 2)
	{
		ft_putstr("Please don't input more than one file\n");
		return (-1);
	}
	if (ft_strnstr(argv[1], "fdf", ft_strlen(argv[1])))
		return (handle_fdf(argv, data));
	//else if (ft_strnstr(argv[1], "obj", ft_strlen(argv[1])))
	//	handle_obj(argv, data);
	else
	{
		ft_putstr("Please input the correcte file format (.fdf or .obj)\n");
		return (-1);
	}
	return (0);
}
