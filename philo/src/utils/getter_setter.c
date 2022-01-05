/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 00:05:20 by toni              #+#    #+#             */
/*   Updated: 2022/01/05 20:02:06 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_data	*_get_data(t_data *data, bool set)
{
	static t_data	*static_data = NULL;

	if (set)
		static_data = data;
	return (static_data);
}

void	set_data(t_data *data)
{
	_get_data(data, true);
}

t_data	*get_data(void)
{
	t_data	*data;

	data = _get_data(NULL, false);
	if (data == NULL)
		prnt_error("Warning: Address cannot be accessed\n", false);
	return (data);
}
