/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_worker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 23:58:39 by toni              #+#    #+#             */
/*   Updated: 2022/01/07 18:19:50 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philos_waiting_in_queue(void)
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

static void	*philo_queue(void *arg)
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

static int	create_philo_threads(t_philo *philos, t_uint no_of_philos)
{
	t_uint	i;

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

static void	join_threads(t_philo *philos)
{
	t_uint	i;

	i = 0;
	while (i < get_data()->prog_args[no_of_philos])
	{
		if (pthread_join(philos[i].philos_thread, NULL) != 0)
			prnt_error("Failed to join thread", true);
		i++;
	}
}

static bool	no_one_hungry(t_philo *philos, t_uint no_of_philos)
{
	t_uint	i;

	i = 0;
	while (i < no_of_philos)
	{
		pthread_mutex_lock(&philos[i].finished_mutex);
		if (philos[i].finished_eating == false)
		{
			pthread_mutex_unlock(&philos[i].finished_mutex);
			return (false);
		}
		pthread_mutex_unlock(&philos[i].finished_mutex);
		i++;
	}
	return (true);
}

static bool	philo_is_idle(t_philo *philo)
{
	bool	finished_eating;
	bool	is_eating;

	pthread_mutex_lock(&philo->finished_mutex);
	finished_eating = philo->finished_eating;
	pthread_mutex_unlock(&philo->finished_mutex);
	if (finished_eating)
		return (false);
	pthread_mutex_lock(&philo->eating_mutex);
	is_eating = philo->is_eating;
	pthread_mutex_unlock(&philo->eating_mutex);
	if (is_eating)
		return (false);
	return (true);
}

void	detach_threads(t_philo *philos, t_uint no_of_philos)
{
	t_uint	i;

	i = 0;
	while (i < no_of_philos)
	{
		if (pthread_detach(philos[i].philos_thread) != 0)
			prnt_error("Failed to detach thread", true);
		i++;
	}
}

static inline bool	philo_is_dead(t_philo *philo, const t_uint die_time)
{
	return (
		(philo_is_idle(philo) \
		&& (get_curr_time().ms - philo->last_meal.ms > die_time) \
		&& philo_is_idle(philo)) \
		);
}

static size_t	check_dead(t_data *data)
{
	t_uint			i;
	const t_uint	die_time = data->prog_args[1];

	while (true)
	{
		i = 0;
		while (i < data->prog_args[no_of_philos])
		{
			if (philo_is_dead(&data->philos_data[i], die_time))
			{
				pthread_mutex_lock(&get_data()->died_mutex);
				data->philo_died = true;
				pthread_mutex_unlock(&get_data()->died_mutex);
				join_threads(data->philos_data);
				philo_print("is dead", i + 1);
				return (EXIT_FAILURE);
			}
			i++;
		}
		if (no_one_hungry(data->philos_data, data->prog_args[no_of_philos]))
		{
			join_threads(data->philos_data);
			return (EXIT_SUCCESS);
		}
	}
}

void	*thread_woker(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	data->philo_died = false;
	if (create_philo_threads(data->philos_data, data->prog_args[no_of_philos]) \
	== EXIT_FAILURE)
		return ((void *)EXIT_FAILURE);
	while (philos_waiting_in_queue() == false)
		usleep(1);
	usleep((get_data()->prog_args[time_to_die] / 2) * 1000);
	return ((void *)check_dead(data));
}
