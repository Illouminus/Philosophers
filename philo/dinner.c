/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:19:16 by edouard           #+#    #+#             */
/*   Updated: 2024/06/13 07:12:29 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void *lone_philo(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_for_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex, &philo->table->threads_running_number);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}
void thinking(t_philo *philo, bool pre_sim)
{
	long t_eat;
	long t_sleep;
	long t_think;

	if (!pre_sim)
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->nb_philo % 2 == 0)
		return;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(t_think * 0.2, philo->table);
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

	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECOND));

	increase_long(&philo->table->table_mutex, &philo->table->threads_running_number);

	de_sync_philos(philo);
	while (!simulation_finished(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->is_full))
			break;
		philo_eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
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
		safe_thread_handler(&table->philos[0].thread_id, lone_philo, &table->philos[0], CREATE);
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
	{
		safe_thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
	}

	set_bool(&table->table_mutex, &table->is_dead, true);
	safe_thread_handler(&table->monitor, NULL, NULL, JOIN);
}