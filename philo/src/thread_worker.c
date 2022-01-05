/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_worker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 23:58:39 by toni              #+#    #+#             */
/*   Updated: 2022/01/05 14:56:33 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philo_threads(t_data *data, uint no_of_threads)
{
	uint	i;

	data->philos_threads = ft_calloc(no_of_threads + 1, sizeof(*data->philos_threads));
	if (data->philos_threads == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < no_of_threads)
	{
		if (pthread_mutex_init(&data->philos_data[i].last_meal.mutex, NULL) != 0)
		{
			ft_free((void *)&data->philos_threads);
			prnt_error("Error creating mutex\n", false);
			return (EXIT_FAILURE);
		}
		data->philos_data[i].last_meal.type = T_TIME;
		data->philos_data[i].last_meal.data.t = data->start_time;
		if (pthread_create(&data->philos_threads[i], NULL, philo_routine, &data->philos_data[i]) != 0)
		{
			ft_free((void *)&data->philos_threads);
			prnt_error("Error creating thread\n", false);
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
	if (create_philo_threads(data, data->prog_args[no_of_philos]) == EXIT_FAILURE)
		return ((void *)EXIT_FAILURE);
	check_dead(data);
	return (NULL);
}