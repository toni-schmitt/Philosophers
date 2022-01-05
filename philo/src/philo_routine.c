/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:51:11 by toni              #+#    #+#             */
/*   Updated: 2022/01/05 19:49:44 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(t_philo *philo)
{
	uint	meals_eaten;

	philo->last_meal = get_data()->start_time;
	meals_eaten = 0;
	philo_think(philo);
	while (true)
	{
		philo->last_meal = philo_eat(philo);
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
		philo_think(philo);
		if (philo->finished_eating)
		{
			fprintf(stderr, "Philo %d finished eating\n", philo->id);
			return (NULL);
		}
	}
	return (PTHREAD_CANCELED);
}
