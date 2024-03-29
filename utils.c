/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:10:38 by aliaudet          #+#    #+#             */
/*   Updated: 2023/10/19 16:53:31 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "fdf.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((!big || !little) && len == 0)
		return (NULL);
	if (!little[0])
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && little[j]
			&& big[i + j] == little[j] && (i + j) < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)&(big[i]));
			j++;
		}
		i++;
	}
	return (NULL);
}

int	ft_atoi(const char *str)
{
	t_count	c;

	c = (t_count){0, 0, 0};
	while (*str == ' ' || *str == '\t' || *str == '\r'
		|| *str == '\n' || *str == '\v' || *str == '\f')
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			c.i++;
		if (*str == '+')
			c.j++;
		str++;
	}
	while ((*str >= '0' && *str <= '9') || *str == '.')
	{
		if (*str == '.')
			str++;
		c.k = c.k * 10 + *str++ - '0';
	}
	if ((c.i + c.j) > 1)
		return (0);
	if (c.i == 1)
		c.k = -c.k;
	return (c.k);
}

int	countw(const char *s)
{
	int	i;
	int	count;
	int	trigger;

	i = 0;
	count = 0;
	trigger = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\n' && trigger == 0)
		{
			trigger = 1;
			count++;
		}
		else if (s[i] == ' ')
			trigger = 0;
		i++;
	}
	return (count);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ((unsigned char)s1[i] || (unsigned char)s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_putstr(const char *str)
{
	while (*str)
		write(1, &*str++, 1);
}
