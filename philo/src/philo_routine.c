/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:51:11 by toni              #+#    #+#             */
/*   Updated: 2022/01/06 18:08:48 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(t_philo *philo)
{
	uint	meals_eaten;

	meals_eaten = 0;
	philo_think(philo);
	if (philo->id % 2 == 0)
	{
		if (get_data()->prog_args[no_of_philos] > 10)
			usleep(10000);
		else
			usleep(5000);
	}
	while (true)
	{
		philo->last_meal = philo_eat(philo);
		if (get_data()->philo_died)
			return (PTHREAD_CANCELED);
		meals_eaten++;
		if (get_data()->prog_args[no_of_min_meals_given])
		{
			if (meals_eaten >= get_data()->prog_args[no_of_min_meals])
			{
				pthread_mutex_lock(&philo->finished_mutex);
				philo->finished_eating = true;
				pthread_mutex_unlock(&philo->finished_mutex);
			}
		}
		philo_sleep(philo);
		if (get_data()->philo_died)
			return (PTHREAD_CANCELED);
		philo_think(philo);
		if (get_data()->philo_died)
			return (PTHREAD_CANCELED);
		if (philo->finished_eating)
		{
			return (NULL);
		}
	}
	return (PTHREAD_CANCELED);
}
