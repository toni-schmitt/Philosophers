/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 23:34:16 by toni              #+#    #+#             */
/*   Updated: 2022/01/04 00:00:39 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define ERROR_MUTEX_INIT "Error initializing mutexes\n"

static t_mutex	*create_forks(uint no_of_forks)
{
	t_mutex	*forks;
	uint	i;

	forks = ft_calloc(no_of_forks + 1, sizeof(*forks));
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < no_of_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free(forks);
			prnt_error(ERROR_MUTEX_INIT, false);
			return (NULL);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	create_mutexes(t_data *data)
{
	data->forks = create_forks(data->prog_args[no_of_philos] / 2);
	if (data->forks == NULL)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		prnt_error(ERROR_MUTEX_INIT, false);
		ft_free((void *)&data->forks);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	create_philos_data(t_data *data)
{
	uint	i;

	data->philos_data = ft_calloc(data->prog_args[no_of_philos] + 1, sizeof(*data->philos_data));
	if (data->philos_data == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < data->prog_args[no_of_philos])
	{
		data->philos_data[i].id = i;
		data->philos_data[i].last_meal.type = T_TIME;
		if (pthread_mutex_init(&data->philos_data[i].last_meal.mutex, NULL) != 0)
		{
			ft_free((void *)&data->philos_data);
			prnt_error(ERROR_MUTEX_INIT, false);
			return (EXIT_FAILURE);
		}
		if (i == 0)
			data->philos_data[i].left_fork = &data->forks[data->prog_args[no_of_philos] - 1];
		else
			data->philos_data[i].left_fork = &data->forks[i - 1];
		data->philos_data[i].right_fork = &data->forks[i];
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	create_thread_worker(t_data *data)
{
	t_thread	worker;
	void		*worker_retval;

	if (pthread_create(&worker, NULL, thread_woker, data) != 0)
		return (EXIT_FAILURE);
	if (pthread_join(worker, &worker_retval) != 0)
	{
		free(data->philos_data);
		free(data->forks);
		free(data);
		return (EXIT_FAILURE);
	}
	return ((size_t)worker_retval);
}

int	init_philos(t_data *data)
{
	if (create_mutexes(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_philos_data(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_thread_worker(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}