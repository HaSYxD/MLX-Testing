#include "utils.h"
#include "fdf.h"
#include "get_next_line.h"
#include "file_handling.h"

void	handle_obj(char *argv[], t_data *data)
{
	static char	*raw;
	char		*buff;
	int			fd;

	fd = open(argv[1], O_RDONLY);
	data->obj.num_vert = 0;
	while (get_next_line(fd, &buff) && *buff != '\0')
	{
		if (buff[0] == 'v' && buff[1] == ' ')
		{
			data->obj.num_vert++;
			raw = ft_strjoin(raw, buff);
		}
		if (buff[0] == 'f')
			raw = ft_strjoin(raw, buff);
	}
	//printf("%s", raw);
	//printf("%d\n", data->obj.num_vert);
	free(raw);
	free(buff);
	close(fd);
}