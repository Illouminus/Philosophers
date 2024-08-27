/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:02:17 by edouard           #+#    #+#             */
/*   Updated: 2024/08/27 11:13:26 by edouard          ###   ########.fr       */
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

int check_if_philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_mutex);
	if (philo->table->is_dead)
	{
		pthread_mutex_unlock(&philo->table->dead_mutex);
		return 1;
	}
	pthread_mutex_unlock(&philo->table->dead_mutex);
	return 0;
}

int check_if_philo_is_full(t_philo *philo)
{
	if (philo->table->nb_limit_meals != -1 && philo->nb_meals >= philo->table->nb_limit_meals)
	{
		write_status(philo, "is full");
		pthread_mutex_lock(&philo->philo_mutex);
		philo->is_full = true;
		pthread_mutex_unlock(&philo->philo_mutex);
		return 1;
	}
	return 0;
}