/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 21:51:12 by toni              #+#    #+#             */
/*   Updated: 2022/01/03 21:53:08 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}

static bool	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

uint	atoui(char *str)
{
	uint	n;

	n = 0;
	while (is_space(*str))
		str++;
	while (is_digit(*str))
	{
		n = (n * 10) + (*str - '0');
		str++;
	}
	return (n);
}

void	*ft_calloc(size_t count, size_t size)
{
	int		full_size;
	void	*buf;

	full_size = size * count;
	buf = malloc(full_size);
	if (buf == NULL)
		return (NULL);
	return (memset(buf, 0, full_size));
}
