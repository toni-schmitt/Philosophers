/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_worker_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 20:44:26 by toni              #+#    #+#             */
/*   Updated: 2022/01/11 21:27:27 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philos_waiting_in_queue(void)
{
	pthread_mutex_lock(&get_data()->philo_queue);
	if (get_data()->waiting_in_queue == get_data()->prog_args[no_of_philos])
	{
		pthread_mutex_unlock(&get_data()->philo_queue);
		return (true);
	}
	pthread_mutex_unlock(&get_data()->philo_queue);
	return (false);
}

void	*philo_queue(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&get_data()->philo_queue);
	get_data()->start_time = get_curr_time();
	get_data()->waiting_in_queue++;
	pthread_mutex_unlock(&get_data()->philo_queue);
	while (philos_waiting_in_queue() == false)
		usleep(1);
	pthread_mutex_lock(&get_data()->philo_queue);
	philo->last_meal = get_data()->start_time;
	pthread_mutex_unlock(&get_data()->philo_queue);
	return (philo_routine(philo));
}

int_fast32_t	create_philo_threads(
	t_philo *philos, uint_fast32_t no_of_philos
	)
{
	uint_fast32_t	i;

	i = 0;
	while (i < no_of_philos)
	{
		if (pthread_create(&philos[i].philos_thread, NULL, \
			philo_queue, &philos[i]) != 0)
		{
			prnt_error("Error creating philo-thread", true);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	join_threads(t_philo *philos)
{
	uint_fast32_t	i;

	i = 0;
	while (i < get_data()->prog_args[no_of_philos])
	{
		if (pthread_join(philos[i].philos_thread, NULL) != 0)
			prnt_error("Failed to join thread", true);
		i++;
	}
}
