/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_worker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 23:58:39 by toni              #+#    #+#             */
/*   Updated: 2022/01/05 20:27:03 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_queue(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&get_data()->philo_queue);
	get_data()->start_time = get_curr_time();
	get_data()->waiting_in_queue++;
	pthread_mutex_unlock(&get_data()->philo_queue);
	while (get_data()->waiting_in_queue != get_data()->prog_args[no_of_philos])
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

static void	join_threads(t_philo *philos)
{
	uint	i;

	i = 0;
	while (i < get_data()->prog_args[no_of_philos])
	{
		if (pthread_join(philos[i].philos_thread, NULL) != 0)
			prnt_error("Failed to join thread", true);
		i++;
	}
}

static void	check_dead(t_data *data)
{
	uint	i;

	while (true)
	{
		i = 0;
		while (i < data->prog_args[no_of_philos])
		{
			if (get_curr_time().ms - data->philos_data[i].last_meal.ms >= data->prog_args[time_to_die])
			{
				pthread_mutex_lock(&data->philos_data[i].finished_mutex);
				if (!data->philos_data[i].finished_eating)
				{
					pthread_mutex_unlock(&data->philos_data[i].finished_mutex);
					data->philo_died = true;
					join_threads(data->philos_data);
					philo_print("is dead", i + 1);
					return ;
				}
				pthread_mutex_unlock(&data->philos_data[i].finished_mutex);
			}
			i++;
		}
	}
}

void	*thread_woker(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	data->philo_died = false;
	if (create_philo_threads(data->philos_data, data->prog_args[no_of_philos]) == EXIT_FAILURE)
		return ((void *)EXIT_FAILURE);
	while (get_data()->waiting_in_queue != get_data()->prog_args[no_of_philos])
		;
	philo_thread_sleep_ms(get_data()->prog_args[time_to_die] / 2);
	check_dead(data);
	return (NULL);
}