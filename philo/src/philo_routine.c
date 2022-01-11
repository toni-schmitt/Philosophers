/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:51:11 by toni              #+#    #+#             */
/*   Updated: 2022/01/11 21:29:32 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	one_philo_died(void)
{
	bool	retval;

	pthread_mutex_lock(&get_data()->died_mutex);
	retval = get_data()->philo_died;
	pthread_mutex_unlock(&get_data()->died_mutex);
	return (retval);
}

static void	*philo_doze(t_philo *philo)
{
	philo_sleep(philo);
	if (one_philo_died())
		return (PTHREAD_CANCELED);
	philo_think(philo);
	if (one_philo_died())
		return (PTHREAD_CANCELED);
	return (NULL);
}

void	*philo_routine(t_philo *philo)
{
	uint_fast32_t		meals_eaten;
	const uint_fast32_t	no_of_min_meals = get_data()->prog_args[4];
	const bool			no_of_min_meals_given = get_data()->prog_args[5];

	meals_eaten = 0;
	philo_think(philo);
	if (philo->id % 2 == 0)
		usleep(5000);
	while (true)
	{
		philo_eat(philo);
		if (one_philo_died())
			return (PTHREAD_CANCELED);
		if ((no_of_min_meals_given) && (++meals_eaten >= no_of_min_meals))
		{
			pthread_mutex_lock(&philo->finished_mutex);
			philo->finished_eating = true;
			pthread_mutex_unlock(&philo->finished_mutex);
		}
		if (philo_doze(philo) == PTHREAD_CANCELED)
			return (PTHREAD_CANCELED);
		if (philo->finished_eating)
			return (NULL);
	}
}
