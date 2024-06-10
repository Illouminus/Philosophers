/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:19:16 by edouard           #+#    #+#             */
/*   Updated: 2024/06/10 17:26:04 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void *dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_for_all_threads(philo->table); // TODO
	return (NULL);
}

void start_dinner(t_table *table)
{
	int i;

	i = -1;
	if (!table->nb_limit_meals)
		return;
	else if (table->nb_philo == 1)
		; // TODO
	else
	{
		while (++i < table->nb_philo)
			safe_thread_handler(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE);
	}
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
}