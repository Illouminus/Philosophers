/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:51:21 by edouard           #+#    #+#             */
/*   Updated: 2024/09/24 17:40:23 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	write_status(t_philo *philo, const char *status)
{
	long	current_time;

	current_time = get_current_time_in_ms();
	pthread_mutex_lock(&philo->table->write_mutex);
	pthread_mutex_lock(&philo->table->dead_mutex);
	if (!philo->table->is_dead)
	{
		printf("%ld %d %s\n", current_time - philo->table->start_time,
			philo->id, status);
	}
	pthread_mutex_unlock(&philo->table->dead_mutex);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}
