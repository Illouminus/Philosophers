/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:19:16 by edouard           #+#    #+#             */
/*   Updated: 2024/06/10 19:09:31 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void philo_eat(t_philo *philo)
{
	safe_mutex_handler(&philo->left_fork->fork, LOCK);
	write_status(philo, TAKE_FIRST_FORK, DEBUG_MODE);
	safe_mutex_handler(&philo->right_fork->fork, LOCK);
	write_status(philo, TAKE_SECOND_FORK, DEBUG_MODE);
}

void *dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_for_all_threads(philo->table);

	while (!simulation_finished(philo->table))
	{
		if (get_bool(&philo->table->table_mutex, &philo->table->is_dead))
			break;
		philo_eat(philo);
		write_status(philo, SLEEPING, DEBUG_MODE);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		philo_think(philo);
	}
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
	table->start_time = get_time(MICROSECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);

	i = -1;
	while (++i < table->nb_philo)
		safe_thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
}