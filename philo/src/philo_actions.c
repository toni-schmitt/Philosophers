/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:51:02 by toni              #+#    #+#             */
/*   Updated: 2022/01/07 20:10:00 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define PHILO_FORK "has taken a fork"
#define PHILO_EAT "is eating"
#define PHILO_SLEEP "is sleeping"
#define PHILO_THINK "is thinking"

#define PHILO_DEAD 125

bool	one_philo_died(void)
{
	bool	retval;

	pthread_mutex_lock(&get_data()->died_mutex);
	retval = get_data()->philo_died;
	pthread_mutex_unlock(&get_data()->died_mutex);
	return (retval);
}

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
	if (one_philo_died())
		return (PHILO_DEAD);
	pthread_mutex_lock(left);
	if (one_philo_died())
	{
		give_forks(philo_id, left, NULL);
		return (PHILO_DEAD);
	}
	philo_print(PHILO_FORK, philo_id);
	pthread_mutex_lock(right);
	usleep(200);
	if (one_philo_died())
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

void	philo_eat(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
	{
		handle_lonely_philo(philo);
		return ;
	}
	if (take_forks(philo->id, philo->left_fork, philo->right_fork) == 125)
		return ;
	update_eating(philo, true);
	philo->last_meal = philo_print(PHILO_EAT, philo->id);
	philo_thread_sleep_ms(get_data()->prog_args[time_to_eat]);
	update_eating(philo, false);
	give_forks(philo->id, philo->left_fork, philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	usleep(100);
	if (one_philo_died())
		return ;
	philo_print(PHILO_SLEEP, philo->id);
	philo_thread_sleep_ms(get_data()->prog_args[time_to_sleep]);
}

void	philo_think(t_philo *philo)
{
	usleep(100);
	if (one_philo_died())
		return ;
	philo_print(PHILO_THINK, philo->id);
}
