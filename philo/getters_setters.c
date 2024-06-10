/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:10:08 by edouard           #+#    #+#             */
/*   Updated: 2024/06/10 17:25:19 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void set_bool(t_mutex *mutex, bool *dest, bool value)
{
	safe_mutex_handler(mutex, LOCK);
	*dest = value;
	safe_mutex_handler(mutex, UNLOCK);
}

bool get_bool(t_mutex *mutex, bool *src)
{
	bool value;

	safe_mutex_handler(mutex, LOCK);
	value = *src;
	safe_mutex_handler(mutex, UNLOCK);
	return (value);
}

void set_long(t_mutex *mutex, long *dest, bool value)
{
	safe_mutex_handler(mutex, LOCK);
	*dest = value;
	safe_mutex_handler(mutex, UNLOCK);
}

long get_long(t_mutex *mutex, long *src)
{
	bool value;

	safe_mutex_handler(mutex, LOCK);
	value = *src;
	safe_mutex_handler(mutex, UNLOCK);
	return (value);
}

bool simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->is_dead));
}