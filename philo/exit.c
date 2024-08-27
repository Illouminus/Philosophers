/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:10:42 by edouard           #+#    #+#             */
/*   Updated: 2024/08/27 11:12:33 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void join_threads(t_table *table)
{
	int i = 0;
	if (table->philos[i].thread_id)
		while (i < table->nb_philo)
		{
			if (table->philos[i].thread_id)
				pthread_join(table->philos[i].thread_id, NULL);
			i++;
		}
}

void destroy_mutexes(t_table *table)
{
	int i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
		i++;
	}

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		i++;
	}

	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->dead_mutex);
}

void free_resources(t_table *table)
{
	free(table->philos);
	free(table->forks);
}

void clean_exit(t_table *table)
{
	join_threads(table);
	destroy_mutexes(table);
	free_resources(table);
}