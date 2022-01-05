/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 21:46:47 by toni              #+#    #+#             */
/*   Updated: 2022/01/05 19:37:51 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_numerical(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

uint	*get_prog_args(int argc, char *argv[])
{
	uint	*prog_args;
	int		i;

	prog_args = ft_calloc(argc + 1, sizeof(*prog_args));
	if (prog_args == NULL)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) > 10 || argv[i][0] == '-' \
		|| !is_numerical(argv[i]))
		{
			free(prog_args);
			prnt_error("Error: Argument out of range\n", true);
			return (NULL);
		}
		prog_args[i] = atoui(argv[i]);
		i++;
	}
	if (argc == 6)
		prog_args[no_of_min_meals_given] = true;
	else
		prog_args[no_of_min_meals_given] = false;
	return (prog_args);
}

t_data	*parse_input(int argc, char *argv[])
{
	t_data	*data;

	data = ft_calloc(1, sizeof(*data));
	if (data == NULL)
		return (NULL);
	data->prog_args = get_prog_args(argc, argv + 1);
	if (data->prog_args == NULL)
		return (NULL);
	return (data);
}
