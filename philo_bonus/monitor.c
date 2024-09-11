/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:13:29 by edouard           #+#    #+#             */
/*   Updated: 2024/09/11 18:47:53 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->philo_sem);
		if (philo->next_meal < get_current_time_in_ms())
		{
			write_status(philo, "died");
			sem_wait(philo->table->block_dead);
			philo->table->dead = true;
			sem_post(philo->table->block_dead);
			sem_post(philo->philo_sem);
			sem_post(philo->table->dead_sem);
			break ;
		}
		if (philo->table->nb_limit_meals != -1 && philo->nb_meals >= philo->table->nb_limit_meals )
		{
			sem_post(philo->table->full_philos_sem); 
			sem_post(philo->philo_sem);
			sem_post(philo->table->dead_sem);
			break;
		}
		sem_post(philo->philo_sem);
	}
	return (NULL);
}
