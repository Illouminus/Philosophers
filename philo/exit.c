/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:10:42 by edouard           #+#    #+#             */
/*   Updated: 2024/09/24 17:38:58 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	if (table->philos[i].thread_id)
	{
		while (i < table->nb_philo)
		{
			if (table->philos[i].thread_id)
				pthread_join(table->philos[i].thread_id, NULL);
			i++;
		}
	}
}

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
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

void	free_resources(t_table *table)
{
	free(table->philos);
	free(table->forks);
}

void	clean_exit(t_table *table)
{
	if (table->nb_philo != 1)
		join_threads(table);
	destroy_mutexes(table);
	free_resources(table);
}
