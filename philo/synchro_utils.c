/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:29:17 by edouard           #+#    #+#             */
/*   Updated: 2024/06/12 16:47:42 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void wait_for_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

bool all_threads_running(t_table *table)
{
}

void increase_long(t_mutex *mutex, long *value)
{
	safe_mutex_handler(mutex, LOCK);
	(*value)++;
	safe_mutex_handler(mutex, UNLOCK);
}