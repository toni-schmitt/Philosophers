/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_worker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 23:58:39 by toni              #+#    #+#             */
/*   Updated: 2022/01/05 15:51:25 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_queue(void *arg)
{
	t_philo		*philo;
	static uint	waiting_in_queue = 0;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&get_data()->philo_queue);
	get_data()->start_time = get_curr_time();
	waiting_in_queue++;
	pthread_mutex_lock(&get_data()->philo_queue);
	while (waiting_in_queue != get_data()->prog_args[no_of_philos])
		;
	return (philo_routine(philo));
}

static int	create_philo_threads(t_philo *philos, uint no_of_philos)
{
	uint	i;

	i = 0;
	while (i < no_of_philos)
	{
		if (pthread_create(&philos[i].philos_thread, NULL, philo_queue, &philos[i]) != 0)
		{
			prnt_error("Error creating philo-thread", true);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	check_dead(t_data *data)
{
	(void)data;
}

void	*thread_woker(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (create_philo_threads(data->philos_data, data->prog_args[no_of_philos]) == EXIT_FAILURE)
		return ((void *)EXIT_FAILURE);
	check_dead(data);
	return (NULL);
}