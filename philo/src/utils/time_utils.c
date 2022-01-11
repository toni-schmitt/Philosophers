/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:02:11 by toni              #+#    #+#             */
/*   Updated: 2022/01/11 21:02:16 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint_fast64_t	timeval_to_ms(struct timeval time)
{
	return ((time.tv_sec * (uint_fast64_t)1000) + (time.tv_usec / 1000));
}

t_time	get_curr_time(void)
{
	t_time	curr_time;

	gettimeofday(&curr_time.val, NULL);
	curr_time.ms = timeval_to_ms(curr_time.val);
	return (curr_time);
}

void	philo_thread_sleep_ms(uint_fast64_t ms)
{
	uint_fast64_t	end;
	uint_fast32_t	sleep_time;

	if (get_data()->prog_args[no_of_philos] >= 50)
		sleep_time = 500;
	else
		sleep_time = 100;
	end = get_curr_time().ms + ms;
	while (get_curr_time().ms <= end)
	{
		if (one_philo_died())
			break ;
		usleep(sleep_time);
	}
}
