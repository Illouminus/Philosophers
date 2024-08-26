/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:02:17 by edouard           #+#    #+#             */
/*   Updated: 2024/08/24 08:14:32 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

long get_current_time_in_ms(void)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
}

void ft_usleep(long time_in_ms)
{
	long start_time = get_current_time_in_ms();
	long end_time = start_time + time_in_ms;
	while (get_current_time_in_ms() < end_time)
		usleep(100);
}

int error_handler(const char *message)
{
	printf("Error: %s\n", message);
	return 1;
}

void clean_exit(t_table *table)
{
	// Уничтожаем мьютексы философов
	for (int i = 0; i < table->nb_philo; i++)
	{
		pthread_join(table->philos[i].thread_id, NULL);
	}

	for (int i = 0; i < table->nb_philo; i++)
	{
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
	}

	// Уничтожаем мьютексы вилок
	for (int i = 0; i < table->nb_philo; i++)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
	}

	// Уничтожаем другие мьютексы
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->dead_mutex);

	// Освобождаем выделенную память
	free(table->philos);
	free(table->forks);
}
