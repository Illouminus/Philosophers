/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:29:17 by edouard           #+#    #+#             */
/*   Updated: 2024/06/12 16:50:25 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void wait_for_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

bool all_threads_running(t_mutex *mutex, long *threads, long philo_nbr)
{
	bool ret;

	ret = false;
	safe_mutex_handler(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handler(mutex, UNLOCK);
	return (ret);
}

void increase_long(t_mutex *mutex, long *value)
{
	safe_mutex_handler(mutex, LOCK);
	(*value)++;
	safe_mutex_handler(mutex, UNLOCK);
}