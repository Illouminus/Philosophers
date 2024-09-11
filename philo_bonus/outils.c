/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:02:17 by edouard           #+#    #+#             */
/*   Updated: 2024/09/11 18:48:50 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

long	get_current_time_in_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ft_usleep(long time_in_ms)
{
	long	start_time;
	long	end_time;

	start_time = get_current_time_in_ms();
	end_time = start_time + time_in_ms;
	while (get_current_time_in_ms() < end_time)
		usleep(10);
}

int	error_handler(const char *message)
{
	printf("Error: %s\n", message);
	return (1);
}

void	write_status(t_philo *philo, const char *status)
{
	long	current_time;

	sem_wait(philo->table->write_sem);

	sem_wait(philo->table->block_dead);
	if (philo->table->dead) 
	{
		printf("%ld %d %s\n", get_current_time_in_ms() - philo->table->start_time,
			philo->id, "died");
		sem_post(philo->table->block_dead);
		sem_post(philo->table->write_sem);
		return;
	}
	sem_post(philo->table->block_dead);

	current_time = get_current_time_in_ms();
	printf("%ld %d %s\n", current_time - philo->table->start_time, philo->id,
		status);

	sem_post(philo->table->write_sem);
}


bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}
