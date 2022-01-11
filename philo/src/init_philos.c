/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 23:34:16 by toni              #+#    #+#             */
/*   Updated: 2022/01/11 21:27:45 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define ERROR_MUTEX_INIT "Error initializing mutexes\n"

static t_mutex	*create_forks(uint_fast32_t no_of_forks)
{
	t_mutex			*forks;
	uint_fast32_t	i;

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
	return (forks);
}

static int_fast32_t	create_mutexes(t_data *data)
{
	data->forks = create_forks(data->prog_args[no_of_philos]);
	if (data->forks == NULL)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0 \
	|| pthread_mutex_init(&data->philo_queue, NULL) != 0 \
	|| pthread_mutex_init(&data->died_mutex, NULL) != 0)
	{
		prnt_error(ERROR_MUTEX_INIT, false);
		ft_free((void *)&data->forks);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int_fast32_t	create_philos_data(t_data *data)
{
	uint_fast32_t			i;
	const uint_fast32_t		no_of_philos = data->prog_args[0];

	data->philos_data = ft_calloc(no_of_philos + 1, sizeof(*data->philos_data));
	if (data->philos_data == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < no_of_philos)
	{
		data->philos_data[i].id = i + 1;
		if (i == 0)
			data->philos_data[i].left_fork = &data->forks[no_of_philos - 1];
		else
			data->philos_data[i].left_fork = &data->forks[i - 1];
		data->philos_data[i].right_fork = &data->forks[i];
		if (pthread_mutex_init(&data->philos_data[i].finished_mutex, NULL) != 0 \
		|| pthread_mutex_init(&data->philos_data[i].eating_mutex, NULL) != 0)
		{
			prnt_error(ERROR_MUTEX_INIT, false);
			ft_free((void *)&data->philos_data);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static size_t	create_thread_worker(t_data *data)
{
	t_thread	worker;
	void		*worker_retval;

	if (pthread_create(&worker, NULL, thread_woker, data) != 0)
		return (EXIT_FAILURE);
	if (pthread_join(worker, &worker_retval) != 0)
	{
		prnt_error("Error while joining thread worker\n", false);
		free(data->philos_data);
		free(data->forks);
		free(data);
		return (EXIT_FAILURE);
	}
	return ((size_t)worker_retval);
}

int_fast32_t	init_philos(t_data *data)
{
	if (create_mutexes(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_philos_data(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_thread_worker(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
