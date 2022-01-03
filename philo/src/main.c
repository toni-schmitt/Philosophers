/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 03:15:48 by toni              #+#    #+#             */
/*   Updated: 2022/01/03 21:46:26 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s [no_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] (no_of_min_meals)\n", argv[0]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
