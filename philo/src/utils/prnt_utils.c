/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prnt_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 21:55:43 by toni              #+#    #+#             */
/*   Updated: 2022/01/05 19:28:11 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief  Prints message to stderr and exits with 1 if exit_prog is true
 * @note   
 * @param  *message: Message to print to stderr
 * @param  exit_prog: If true exit gets called with EXIT_FAILURE
 */
void	prnt_error(char *message, bool exit_prog)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	if (exit_prog)
	{
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief  Prints message with philo_id and a timestamp
 * @note   
 * @param  *message: Message to print
 * @param  philo_id: Philo-ID from whom to print message
 * @retval Timestamp of printed message
 */
t_time	philo_print(char *message, uint philo_id)
{
	t_time	current_time;

	pthread_mutex_lock(&get_data()->print_mutex);
	current_time = get_curr_time();
	if (get_data()->philo_died)
	{
		pthread_mutex_unlock(&get_data()->print_mutex);
		return (current_time);
	}
	printf("%ld %d %s\n", current_time.ms - get_data()->start_time.ms, philo_id, message);
	pthread_mutex_unlock(&get_data()->print_mutex);
	return (current_time);
}
