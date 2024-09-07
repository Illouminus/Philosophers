/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:13:29 by edouard           #+#    #+#             */
/*   Updated: 2024/09/07 11:46:43 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void *check_death(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while (1)
	{
		if (philo->next_meal < get_current_time_in_ms())
		{
			write_status(philo, "died");
			sem_post(philo->table->dead_sem);
			break;
		}
		if (philo->table->nb_limit_meals != -1)
			if (philo->nb_meals >= philo->table->nb_limit_meals)
			{
				sem_post(philo->table->dead_sem);
				break;
			}

		ft_usleep(1000);
	}
	return NULL;
}