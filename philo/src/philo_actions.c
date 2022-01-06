/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:51:02 by toni              #+#    #+#             */
/*   Updated: 2022/01/06 19:39:38 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define PHILO_FORK "has taken a fork"
#define PHILO_EAT "is eating"
#define PHILO_SLEEP "is sleeping"
#define PHILO_THINK "is thinking"

#define PHILO_DEAD 125

static void	give_forks(t_uint philo_id, t_mutex *left, t_mutex *right)
{
	if (left != NULL)
	{
		pthread_mutex_unlock(left);
	}
	if (right != NULL)
	{
		pthread_mutex_unlock(right);
	}
	(void)philo_id;
}

static int	take_forks(t_uint philo_id, t_mutex *left, t_mutex *right)
{
	if (left == NULL || right == NULL)
	{
		prnt_error("Fatal error: Address cannot be accessed\n", true);
		return (EXIT_FAILURE);
	}
	if (get_data()->philo_died)
		return (PHILO_DEAD);
	pthread_mutex_lock(left);
	if (get_data()->philo_died)
	{
		give_forks(philo_id, left, NULL);
		return (PHILO_DEAD);
	}
	philo_print(PHILO_FORK, philo_id);
	pthread_mutex_lock(right);
	if (get_data()->philo_died)
	{
		give_forks(philo_id, left, right);
		return (PHILO_DEAD);
	}
	philo_print(PHILO_FORK, philo_id);
	return (EXIT_SUCCESS);
}

static void	update_eating(t_philo *philo, bool new)
{
	pthread_mutex_lock(&philo->eating_mutex);
	philo->is_eating = new;
	pthread_mutex_unlock(&philo->eating_mutex);
}

static t_time	handle_lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo_print(PHILO_FORK, philo->id);
	philo_thread_sleep_ms(get_data()->prog_args[time_to_die]);
	pthread_mutex_unlock(philo->right_fork);
	return (get_data()->start_time);
}

t_time	philo_eat(t_philo *philo)
{
	t_time	print_timestamp;

	if (philo->left_fork == philo->right_fork)
		return (handle_lonely_philo(philo));
	if (take_forks(philo->id, philo->left_fork, philo->right_fork) == PHILO_DEAD)
		return (get_curr_time());
	update_eating(philo, true);
	philo->last_meal = philo_print(PHILO_EAT, philo->id);
	print_timestamp = philo->last_meal;
	philo_thread_sleep_ms(get_data()->prog_args[time_to_eat]);
	update_eating(philo, false);
	give_forks(philo->id, philo->left_fork, philo->right_fork);
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
