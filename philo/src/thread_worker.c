/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_worker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 23:58:39 by toni              #+#    #+#             */
/*   Updated: 2022/01/11 21:03:44 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philos_waiting_in_queue(void);
void	*philo_queue(void *arg);
int_fast32_t		create_philo_threads(t_philo *philos, uint_fast32_t no_of_philos);
void	join_threads(t_philo *philos);

static bool	no_one_hungry(t_philo *philos, uint_fast32_t no_of_philos)
{
	uint_fast32_t	i;

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

static inline bool	philo_is_dead(t_philo *philo, const uint_fast32_t die_time)
{
	return (
		(philo_is_idle(philo) \
		&& (get_curr_time().ms - philo->last_meal.ms > die_time) \
		&& philo_is_idle(philo)) \
		);
}

static size_t	check_dead(t_data *data)
{
	uint_fast32_t			i;
	const uint_fast32_t	die_time = data->prog_args[1];

	while (true)
	{
		i = -1;
		while (++i < data->prog_args[no_of_philos])
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
			usleep(100);
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
		usleep(100);
	usleep((get_data()->prog_args[time_to_die] / 2) * 1000);
	return ((void *)check_dead(data));
}
