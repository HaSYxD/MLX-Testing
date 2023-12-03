#include "ft_printf.h"
#include "utils.h"
#include "fdf.h"
#include "get_next_line.h"
#include "file_handling.h"

t_vect2D	get_min_max(t_data *data)
{
	t_vect2D	mm;
	int	i;
	
	i = 0;
	mm = (t_vect2D){0, 0};
	while (i < data->obj_dt.num_vert)
	{
		if (mm.x > data->obj_dt.vertex[i].x)
			mm.x = data->obj_dt.vertex[i].x;
		if (mm.x > data->obj_dt.vertex[i].y)
			mm.x = data->obj_dt.vertex[i].y;
		if (mm.x > data->obj_dt.vertex[i].z)
			mm.x = data->obj_dt.vertex[i].z;
		if (mm.y < data->obj_dt.vertex[i].x)
			mm.y = data->obj_dt.vertex[i].x;
		if (mm.y < data->obj_dt.vertex[i].y)
			mm.y = data->obj_dt.vertex[i].y;
		if (mm.y < data->obj_dt.vertex[i].z)
			mm.y = data->obj_dt.vertex[i].z;
		i++;
	}
	return (mm);
}

void	normalise_data(t_data *data)
{
	t_vect2D	mm;
	int	i;

	i = 0;
	mm = get_min_max(data);
	while (i < data->obj_dt.num_vert)
	{
		data->obj_dt.vertex[i].x = (2 * ((data->obj_dt.vertex[i].x - mm.x) / (mm.y - mm.x)) - 1);
		data->obj_dt.vertex[i].y = (2 * ((data->obj_dt.vertex[i].y - mm.x) / (mm.y - mm.x)) - 1) * -1;
		data->obj_dt.vertex[i].z = (2 * ((data->obj_dt.vertex[i].z - mm.x) / (mm.y - mm.x)) - 1) * -1;
		i++;
	}
	data->converted = 1;
}

void	convert_fdf_data(t_data *data, char *raw)
{
	t_count	c;
	int	trigger;

	c = (t_count){0, 0, 0};
	trigger = 0;
	while (*raw)
	{
		if ((*raw != ' ' || *raw != '\n') && trigger == 0)
		{
			trigger = 1;
			data->obj_dt.vertex[c.k] = (t_vect3D){c.i, ft_atoi(raw), c.j};
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

void	handle_obj(char *argv[], t_data *data)
{
	static char	*raw;
	char	*buff;
	int	fd;
	
	fd = open(argv[1], O_RDONLY);
	data->obj_dt.num_vert = 0;
	while ((buff = get_next_line(fd)))
	{
		if (buff[0] == 'v' && buff[1] == ' ')
		{
			data->obj_dt.num_vert++;
			raw = ft_strjoin(raw, buff);
		}
		if (buff[0] == 'f')
			raw = ft_strjoin(raw, buff);
	}
	printf("%s", raw);
	printf("%d\n", data->obj_dt.num_vert);
	free(raw);
	free(buff);
	close(fd);
}

int	handle_fdf(char *argv[], t_data *data)
{
	static char	*raw;
	char	*buff;
	int	width_check;
	int	fd;
	
	width_check = 0;
	fd = open(argv[1], O_RDONLY);
	data->obj_dt.map_depth = 0;
	while ((buff = get_next_line(fd)))
	{
		data->obj_dt.map_width = countw(buff, ' ');
		if (width_check == 0)
			width_check = data->obj_dt.map_width;
		raw = ft_strjoin(raw, buff);
		data->obj_dt.map_depth++;
		free(buff);
	}
	if (width_check != data->obj_dt.map_width)
		printf("test\n");
	data->obj_dt.num_vert = data->obj_dt.map_depth * data->obj_dt.map_width;
	data->obj_dt.vertex = malloc(sizeof(t_vect3D) * data->obj_dt.num_vert);
	convert_fdf_data(data, raw);
	free(raw);
	close(fd);
	return (0);
}

int	check_user_input(int argc, char *argv[], t_data *data)
{
	if (argc < 2)
	{
		ft_printf("Please input a file\n");
		return (-1);
	}
	if (argc > 2)
	{
		ft_printf("Please don't input more than one file\n");
		return (-1);
	}
	if (ft_strnstr(argv[1], "fdf", ft_strlen(argv[1])))
		printf("%d", handle_fdf(argv, data));
	else if (ft_strnstr(argv[1], "obj", ft_strlen(argv[1])))
		handle_obj(argv, data);
	else
	{
		ft_printf("Please input the correcte file format (.fdf or .obj)\n");
		return (-1);
	}
	return (0);
}