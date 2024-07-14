/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:04:47 by edouard           #+#    #+#             */
/*   Updated: 2024/07/14 21:29:34 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void write_status(t_philo_status status, t_philo *philo)
{
	long elapsed;

	elapsed = gettime() - philo->data->start;
	sem_wait(philo->data->message);
	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status))
		printf(W "%-6ld" RST " %d has taken a fork\n", elapsed, philo->index);
	else if (EATING == status)
		printf(W "%-6ld" C " %d is eating\n" RST, elapsed, philo->index);
	else if (SLEEPING == status)
		printf(W "%-6ld" RST " %d is sleeping\n", elapsed, philo->index);
	else if (THINKING == status)
		printf(W "%-6ld" RST " %d is thinking\n", elapsed, philo->index);
	else if (FULL == status)
		printf(W "%-6ld" RST " %d is full\n", elapsed, philo->index);
	else if (DIED == status)
		printf(RED "%-6ld %d died\n" RST, elapsed, philo->index);
	sem_post(philo->data->message);
}