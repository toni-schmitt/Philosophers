/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 03:15:31 by toni              #+#    #+#             */
/*   Updated: 2022/01/03 04:09:37 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// INCLUDES

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

// TYPE DEFINITIONS

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

// PHILO-STRUCTS

/**
 * @brief  For accessing time-data (ms, timeval) easily
 */
typedef struct s_time
{
	u_int64_t		ms;
	struct timeval	val;
}	t_time;

/**
 * @brief  For accessing data safely through threads with mutexes
 * @note   Always check for type of data!
 */
typedef struct s_shared_data
{
	enum
	{
		VOID_P,
		INT,
		BOOL,
		T_TIME,
	}	e_type;
	union u_data
	{
		void	*p;
		int		i;
		bool	b;
		t_time	t;
	};
	t_mutex	mutex;
}	t_shared;

/**
 * @brief  Holds data of a philosopher
 */
typedef struct s_philo
{
	uint		id;
	uint		meals_eaten;
	t_shared	last_meal;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
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
};

/**
 * @brief  Holds all program relevant data
 */
typedef struct s_data
{
	// PROGRAM-RELATED DATA
	uint		*prog_args;
	t_shared	start_time;
	t_mutex		print_mutex;
	// PHILO-RELATED DATA
	t_philo		*philos_data;
	t_thread	*philos_threads;
	t_mutex		*forks;
}	t_data;

#endif