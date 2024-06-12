/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:22:17 by edouard           #+#    #+#             */
/*   Updated: 2024/06/12 16:44:14 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int philo_nmbr;

	philo_nmbr = philo->table->nb_philo;
	philo->left_fork = &forks[(philo_position + 1) % philo_nmbr];
	philo->right_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &forks[philo_position];
		philo->right_fork = &forks[(philo_position + 1) % philo_nmbr];
	}
}

static void philo_init(t_table *table)
{
	int i;
	t_philo *philo;

	i = -1;
	while (++i < table->nb_philo)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->is_full = false;
		philo->nb_meals = 0;
		safe_mutex_handler(&philo->philo_mutex, INIT);
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
}

void data_init(t_table *table)
{
	int i;

	i = -1;
	table->is_dead = false;
	table->all_threads_ready = false;
	table->threads_running_number = 0;
	table->philos = safe_malloc(table->nb_philo * sizeof(t_philo));
	table->forks = safe_malloc(table->nb_philo * sizeof(t_fork));
	safe_mutex_handler(&table->write_mutex, INIT);
	safe_mutex_handler(&table->table_mutex, INIT);
	while (++i < table->nb_philo)
	{
		safe_mutex_handler(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}