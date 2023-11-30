#include "ft_printf.h"
#include "utils.h"
#include "fdf.h"
#include "get_next_line.h"
#include "file_handling.h"

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
			data->map_data.map_coords[c.k] = (t_vect3D){c.i, ft_atoi(raw), c.j};
			//printf("%f, %f, %f\n", data->map_data.map_coords[c.k].x, data->map_data.map_coords[c.k].y, data->map_data.map_coords[c.k].z);
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
}

void	handle_fdf(int argc, char *argv[], t_data *data)
{
	static char	*raw;
	char	*buff;
	int	num_vert;
	int	fd;
	
	fd = open(argv[1], O_RDONLY);
	data->map_data.map_depth = 0;
	while (buff = get_next_line(fd))
	{
		data->map_data.map_width = countw(buff, ' ');
		raw = ft_strjoin(raw, buff);
		data->map_data.map_depth++;
	}
	num_vert = data->map_data.map_depth * data->map_data.map_width;
	ft_printf("%d\n", num_vert);
	data->map_data.map_coords = malloc(sizeof(t_vect3D) * num_vert);
	convert_fdf_data(data, raw);
	free(raw);
	free(buff);
	close(fd);
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
		handle_fdf(argc, argv, data);
	else if (ft_strnstr(argv[1], "obj", ft_strlen(argv[1])))
		ft_printf("decoding .obj file...");
	else
	{
		ft_printf("Please input the correcte file format (.fdf or .obj)\n");
		return (-1);
	}
	return (0);
}