#ifndef UTILS_H
# define UTILS_H

# include "stddef.h"
# include "unistd.h"

char	*ft_strnstr(const char *big, const char *little, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_atoi(const char *str);
int	countw(const char *s);
void	ft_putstr(const char *str);

#endif