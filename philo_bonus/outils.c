/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:02:17 by edouard           #+#    #+#             */
/*   Updated: 2024/09/07 11:46:16 by edouard          ###   ########.fr       */
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
	printf("%ld %d %s\n", current_time - philo->table->start_time, philo->id, status);
	sem_post(philo->table->write_sem);
}
