/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:43:20 by edouard           #+#    #+#             */
/*   Updated: 2024/08/24 11:51:57 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

// Функция для инициализации мьютексов вилок
static int init_forks(t_fork *forks, int nb_philo)
{
	int i = 0;
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&forks[i].fork, NULL) != 0)
			return error_handler("initializing fork mutex");
		forks[i].fork_id = i + 1;
		i++;
	}
	return 0;
}

static void init_philosophers(t_philo *philos, t_fork *forks, t_table *table)
{
	int i = 0;
	while (i < table->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].nb_meals = 0;
		philos[i].last_meal = get_current_time_in_ms();
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % table->nb_philo];
		philos[i].table = table;
		pthread_mutex_init(&philos[i].philo_mutex, NULL);
		i++;
	}
}

static int create_philosopher_threads(t_philo *philos, int nb_philo)
{
	int i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&philos[i].thread_id, NULL, dinner_simulation, &philos[i]) != 0)
			return error_handler("creating thread for philosopher");
		i++;
	}
	return 0;
}

// Основная функция для инициализации данных
int data_init(t_table *table)
{
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
		return error_handler("initializing write mutex");

	if (pthread_mutex_init(&table->dead_mutex, NULL) != 0)
		return error_handler("initializing dead mutex");

	table->forks = malloc(sizeof(t_fork) * table->nb_philo);
	if (!table->forks)
		return error_handler("allocating memory for forks");

	if (init_forks(table->forks, table->nb_philo) != 0)
		return 1;

	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		return error_handler("allocating memory for philosophers");

	init_philosophers(table->philos, table->forks, table);

	if (create_philosopher_threads(table->philos, table->nb_philo) != 0)
		return 1;

	return 0;
}