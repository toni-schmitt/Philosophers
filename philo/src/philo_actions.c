/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:51:02 by toni              #+#    #+#             */
/*   Updated: 2022/01/05 14:53:38 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	philo_eat(t_philo *philo)
{
	(void)philo;
	return (get_curr_time());
}

t_time	philo_sleep(t_philo *philo)
{
	(void)philo;
	return (get_curr_time());
}

t_time	philo_think(t_philo *philo)
{
	(void)philo;
	return (get_curr_time());
}
