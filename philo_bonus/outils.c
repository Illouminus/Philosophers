/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:02:17 by edouard           #+#    #+#             */
/*   Updated: 2024/08/29 08:43:48 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

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
		usleep(10);
}

int error_handler(const char *message)
{
	printf("Error: %s\n", message);
	return 1;
}
void write_status(t_philo *philo, const char *status)
{
	long current_time = get_current_time_in_ms();

	sem_wait(philo->table->write_sem);
	sem_wait(philo->table->dead_sem);
	if (!philo->table->is_dead)
		printf("%ld %d %s\n", current_time - philo->table->start_time, philo->id, status);
	sem_post(philo->table->dead_sem);
	sem_post(philo->table->write_sem);
}

int check_if_philo_is_dead_bonus(t_philo *philo)
{
	// printf("Current time: %ld\n", get_current_time_in_ms());
	// printf("Last meal: %ld\n", philo->last_meal);
	// printf("Time to die: %ld\n", philo->table->time_to_die);
	// printf("Difference: %ld\n", get_current_time_in_ms() - philo->last_meal);
	if (get_current_time_in_ms() - philo->last_meal >= philo->table->time_to_die)
	{
		write_status(philo, "died");
		sem_post(philo->table->dead_sem);
		return 1;
	}

	return 0;
}