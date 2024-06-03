/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:22:17 by edouard           #+#    #+#             */
/*   Updated: 2024/06/03 15:49:14 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

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
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->nb_philo];
	}
};

void data_init(t_table *table)
{
	int i;

	i = -1;
	table->is_dead = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->nb_philo);
	table->forks = safe_malloc(sizeof(t_fork) * table->nb_philo);
	while (++i < table->nb_philo)
	{
		safe_mutex_handler(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
}