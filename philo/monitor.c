/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:41:07 by edouard           #+#    #+#             */
/*   Updated: 2024/07/14 17:07:40 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static bool philo_died(t_philo *philo)
{
	long elapsed;
	long t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->is_full))
		return (false);
	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex,
															&philo->last_meal);
	t_to_die = philo->table->time_to_die / 1e3;
	printf("Current time: %ld\n", gettime(MILLISECOND));
	printf("Last meal: %ld\n", philo->last_meal);
	printf("elapsed: %ld\n", elapsed);
	printf("t_to_die: %ld\n", t_to_die);
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void *monitor_simulation(void *data)
{
	t_table *table;
	int i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex, &table->threads_running_number, table->nb_philo))
		usleep(100);
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->nb_philo && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->is_dead, true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
		usleep(100);
	}
	return (NULL);
}
