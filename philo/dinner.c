/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:19:16 by edouard           #+#    #+#             */
/*   Updated: 2024/06/12 16:46:39 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

static void philo_eat(t_philo *philo)
{
	safe_mutex_handler(&philo->left_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handler(&philo->right_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);

	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECOND));
	philo->nb_meals++;
	write_status(EATING, philo, DEBUG_MODE);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nb_limit_meals && philo->nb_meals == philo->table->nb_limit_meals)
		set_bool(&philo->philo_mutex, &philo->is_full, true);
	safe_mutex_handler(&philo->left_fork->fork, UNLOCK);
	safe_mutex_handler(&philo->right_fork->fork, UNLOCK);
}

void *dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;

	wait_for_all_threads(philo->table);
	increase_long(&philo->table->table_mutex, &philo->table->threads_running_number);
	while (!simulation_finished(philo->table))
	{
		if (get_bool(&philo->table->table_mutex, &philo->table->is_dead))
			break;
		philo_eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
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
	safe_thread_handler(&table->monitor, monitor_simulation, table, CREATE);

	table->start_time = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);

	i = -1;
	while (++i < table->nb_philo)
		safe_thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
}