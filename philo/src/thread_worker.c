/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_worker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 23:58:39 by toni              #+#    #+#             */
/*   Updated: 2022/01/05 15:39:25 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philo_threads(t_philo *philos, uint no_of_philos)
{
	uint	i;

	i = 0;
	while (i < no_of_philos)
	{
		if (pthread_create(&philos[i].philos_thread, NULL, philo_routine, &philos[i]) != 0)
		{
			prnt_error("Error creating philo-thread", true);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	check_dead(t_data *data)
{
	(void)data;
}

void	*thread_woker(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	data->start_time = get_curr_time();
	if (create_philo_threads(data->philos_data, data->prog_args[no_of_philos]) == EXIT_FAILURE)
		return ((void *)EXIT_FAILURE);
	check_dead(data);
	return (NULL);
}