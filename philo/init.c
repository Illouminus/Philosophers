/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:22:17 by edouard           #+#    #+#             */
/*   Updated: 2024/06/10 16:59:42 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void assign_forks(t_philo *philos, t_fork *forks, int philo_position)
{
	int philo_nmbr;

	philo_nmbr = philos->table->nb_philo;

	philos->left_fork = &forks[(philo_position + 1) % philo_nmbr];
	philos->right_fork = &forks[philo_position];
	if (philos->id % 2 == 0)
	{
		philos->left_fork = &forks[(philo_position + 1) % philo_nmbr];
		philos->right_fork = &forks[philo_position];
	}
}

static void philo_init(t_table *table)
{
	int i;
	i = -1;
	while (++i < table->nb_philo)
	{
		table->philos[i].id = i;
		table->philos[i].last_meal = get_time();
		table->philos[i].is_full = false;
		table->philos[i].nb_meals = 0;
		table->philos[i].table = table;
		assign_forks(table->philos, table->forks, i);
	}
};

void data_init(t_table *table)
{
	int i;

	i = -1;
	table->is_dead = false;
	table->all_threads_ready = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->nb_philo);
	table->forks = safe_malloc(sizeof(t_fork) * table->nb_philo);
	safe_mutex_handler(&table->table_mutex, INIT);
	while (++i < table->nb_philo)
	{
		safe_mutex_handler(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}