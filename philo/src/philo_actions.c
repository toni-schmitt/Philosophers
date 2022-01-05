/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:51:02 by toni              #+#    #+#             */
/*   Updated: 2022/01/05 19:15:08 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define PHILO_FORK "has taken a fork"
#define PHILO_EAT "is eating"
#define PHILO_SLEEP "is sleeping"
#define PHILO_THINK "is thinking"

#define PHILO_DEAD 125

static int	take_forks(uint philo_id, t_mutex *left, t_mutex *right)
{
	pthread_mutex_lock(left);
	if (get_data()->philo_died)
	{
		give_forks(left, NULL);
		return (PHILO_DEAD);
	}
	philo_print(PHILO_FORK, philo_id);
	pthread_mutex_lock(right);
	if (get_data()->philo_died)
	{
		give_forks(left, right);
		return (PHILO_DEAD);
	}
	philo_print(PHILO_FORK, philo_id);
	return (EXIT_SUCCESS);
}

void	give_forks(t_mutex *left, t_mutex *right)
{
	if (left != NULL)
		pthread_mutex_unlock(left);
	if (right != NULL)
		pthread_mutex_unlock(right);
}

t_time	philo_eat(t_philo *philo)
{
	t_time	print_timestamp;

	if (take_forks(philo->id, philo->left_fork, philo->right_fork) == PHILO_DEAD)
		return (get_curr_time());
	print_timestamp = philo_print(PHILO_EAT, philo->id);
	philo_thread_sleep_ms(get_data()->prog_args[time_to_eat]);
	give_forks(philo->left_fork, philo->right_fork);
	return (print_timestamp);
}

t_time	philo_sleep(t_philo *philo)
{
	t_time	print_timestamp;

	print_timestamp = philo_print(PHILO_SLEEP, philo->id);
	philo_thread_sleep_ms(get_data()->prog_args[time_to_sleep]);
	return (print_timestamp);
}

t_time	philo_think(t_philo *philo)
{
	return (philo_print(PHILO_THINK, philo->id));
}
