#include "stdio.h"
#include "utils.h"
#include "get_next_line.h"

void	handle_fdf(int argc, char *argv[])
{
	char	*buff;
	char	*raw;
	int	fd;
	int	i;
	
	i = 0;
	fd = open(argv[1], O_RDONLY);
	buff = get_next_line(fd);
	printf("%s", buff);
	close(fd);
}

int	check_user_input(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Please input a file\n");
		return (-1);
	}
	if (argc > 2)
	{
		printf("Please don't input more than one file\n");
		return (-1);
	}
	if (ft_strnstr(argv[1], "fdf", ft_strlen(argv[1])))
		handle_fdf(argc, argv);
	else if (ft_strnstr(argv[1], "obj", ft_strlen(argv[1])))
		printf("decoding .obj file...");
	else
	{
		printf("Please input the correcte file format (.fdf or .obj)\n");
		return (-1);
	}
	return (0);
}