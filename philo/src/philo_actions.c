/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:51:02 by toni              #+#    #+#             */
/*   Updated: 2022/01/05 15:13:30 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define PHILO_FORK "has taken a fork"
#define PHILO_EAT "is eating"
#define PHILO_SLEEP "is sleeping"
#define PHILO_THINK "is thinking"

t_time	philo_eat(t_philo *philo)
{
	t_time	print_timestamp;

	pthread_mutex_lock(philo->left_fork);
	philo_print(PHILO_FORK, philo->id);
	pthread_mutex_lock(philo->right_fork);
	philo_print(PHILO_FORK, philo->id);
	print_timestamp = philo_print(PHILO_EAT, philo->id);
	philo_thread_sleep_ms(get_data()->prog_args[time_to_eat]);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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
