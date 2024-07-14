/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:54:40 by edouard           #+#    #+#             */
/*   Updated: 2024/07/14 22:24:10 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void philo_take_fork(t_philo *philo)
{
	sem_wait(philo->data->forks);
	write_status(TAKE_FIRST_FORK, philo);
	sem_wait(philo->data->forks);
	write_status(TAKE_SECOND_FORK, philo);
}

void philo_eat(t_philo *philo)
{
	write_status(EATING, philo);
	if (philo->data->eat_counter != -1)
		philo->data->current_eat++;
	if ((philo->data->eat_counter != -1) && (philo->data->current_eat == philo->data->eat_counter))
	{
		printf("%d is full\n", philo->index);
		philo->is_full = 1;
		return;
	}
	usleep(philo->data->time_to_eat * 1000);
	philo->eating_time = gettime();
	philo->next_meal = philo->eating_time + (unsigned int)philo->data->time_to_die;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void philo_sleep(t_philo *philo)
{
	write_status(SLEEPING, philo);
	usleep(philo->data->time_to_sleep * 1000);
}
