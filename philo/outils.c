/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:02:17 by edouard           #+#    #+#             */
/*   Updated: 2024/08/23 16:47:31 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void ft_usleep(long ms)
{
	struct timeval start;
	struct timeval now;
	long elapsed;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&now, NULL);
		elapsed = (now.tv_sec - start.tv_sec) * 1000 + (now.tv_usec - start.tv_usec) / 1000;
		if (elapsed >= ms)
			break;
		usleep(10);
	}
}

int error_handler(const char *message)
{
	printf("Error: %s\n", message);
	return 1;
}

void clean_exit(t_table *table)
{
	int i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
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
	free(table->philos);
	free(table->forks);
}
