/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:02:11 by toni              #+#    #+#             */
/*   Updated: 2022/01/05 19:08:39 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ulong	timeval_to_ms(struct timeval time)
{
	return ((time.tv_sec * (ulong)1000) + (time.tv_usec / 1000));
}

t_time	get_curr_time(void)
{
	t_time	curr_time;

	gettimeofday(&curr_time.val, NULL);
	curr_time.ms = timeval_to_ms(curr_time.val);
	return (curr_time);
}

void	philo_thread_sleep_ms(ulong ms)
{
	ulong	end;

	end = get_curr_time().ms + ms;
	while (get_curr_time().ms <= end)
	{
		if (get_data()->philo_died)
			break ;
		usleep(1);
	}
}
