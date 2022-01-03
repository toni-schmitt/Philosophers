/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prnt_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 21:55:43 by toni              #+#    #+#             */
/*   Updated: 2022/01/03 22:04:44 by toni             ###   ########.fr       */
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