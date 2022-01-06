/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 03:15:48 by toni              #+#    #+#             */
/*   Updated: 2022/01/06 18:38:43 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s [no_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] (no_of_min_meals)\n", argv[0]);
		return (EXIT_FAILURE);
	}
	data = parse_input(argc, argv);
	if (data == NULL)
		return (EXIT_FAILURE);
	set_data(data);
	if (init_philos(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_free((void *)&data->philos_data);
	ft_free((void *)&data->forks);
	ft_free((void *)&data->prog_args);
	ft_free((void *)&data);
	return (EXIT_SUCCESS);
}
