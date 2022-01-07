/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 03:15:31 by toni              #+#    #+#             */
/*   Updated: 2022/01/06 19:56:53 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// INCLUDES

# include <sys/types.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

// TYPE DEFINITIONS

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef unsigned int	t_uint;
typedef unsigned long	t_ulong;

// PHILO-STRUCTS

/**
 * @brief  For accessing time-data (ms, timeval) easily
 */
typedef struct s_time
{
	t_ulong			ms;
	struct timeval	val;
}	t_time;

/**
 * @brief  Holds data of a philosopher
 */
typedef struct s_philo
{
	t_uint		id;
	bool		finished_eating;
	t_mutex		finished_mutex;
	bool		is_eating;
	t_mutex		eating_mutex;
	t_time		last_meal;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_thread	philos_thread;
}	t_philo;

/**
 * @brief  Index of prog_args array
 */
enum e_arg_index
{
	no_of_philos,
	time_to_die,
	time_to_eat,
	time_to_sleep,
	no_of_min_meals,
	no_of_min_meals_given
};

/**
 * @brief  Holds all program relevant data
 */
typedef struct s_data
{
	// PROGRAM-RELATED DATA
	t_uint		*prog_args;
	t_time		start_time;
	t_mutex		print_mutex;
	// PHILO-RELATED DATA
	t_philo		*philos_data;
	t_mutex		*forks;
	t_uint		waiting_in_queue;
	t_mutex		philo_queue;
	bool		philo_died;
}	t_data;

// FUNCTIONS

t_data	*parse_input(int argc, char *argv[]);
int		init_philos(t_data *data);

// THREAD ROUTINES

void	*thread_woker(void *arg);
void	*philo_routine(t_philo *philo);

// PHILO ACTIONS

void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

// UTILITIES

// PRINT UTILS

void	prnt_error(char *message, bool exit_prog);
t_time	philo_print(char *message, t_uint philo_id);

// STRING UTILS

void	*ft_calloc(size_t count, size_t size);
bool	is_digit(char c);
t_uint	atoui(char *str);
int		ft_strlen(const char *str);
void	*ft_free(void **ptr);

// TIME UTILS

t_ulong	timeval_to_ms(struct timeval time);
t_time	get_curr_time(void);

void	philo_thread_sleep_ms(t_ulong ms);

// GETTER / SETTER

t_data	*get_data(void);
void	set_data(t_data *data);

#endif