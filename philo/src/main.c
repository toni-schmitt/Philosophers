/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 03:15:48 by toni              #+#    #+#             */
/*   Updated: 2022/01/06 19:47:29 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define USAGE "Usage: %s %s %s\n"
#define ARGS "[no_of_philos] [time_to_die] [time_to_eat] [time_to_sleep]"
#define OPT_ARG " (no_of_min_meals)"

static void	free_data(t_data *data)
{
	ft_free((void *)&data->philos_data);
	ft_free((void *)&data->forks);
	ft_free((void *)&data->prog_args);
	ft_free((void *)&data);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		printf(USAGE, argv[0], ARGS, OPT_ARG);
		return (EXIT_FAILURE);
	}
	data = parse_input(argc, argv);
	if (data == NULL)
		return (EXIT_FAILURE);
	set_data(data);
	if (init_philos(data) == EXIT_FAILURE)
	{
		free_data(data);
		return (EXIT_FAILURE);
	}
	free_data(data);
	return (EXIT_SUCCESS);
}
