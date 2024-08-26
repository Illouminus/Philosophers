/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:14:23 by edouard           #+#    #+#             */
/*   Updated: 2024/08/24 11:40:41 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void monitoring(t_table *table)
{
	while (1)
	{
		for (int i = 0; i < table->nb_philo; i++)
		{
			pthread_mutex_lock(&table->philos[i].philo_mutex);

			if (get_current_time_in_ms() - table->philos[i].last_meal > table->time_to_die)
			{
				write_status(&table->philos[i], "died");
				pthread_mutex_lock(&table->dead_mutex);
				table->is_dead = true;
				pthread_mutex_unlock(&table->dead_mutex);
				pthread_mutex_unlock(&table->philos[i].philo_mutex);
				return;
			}
			pthread_mutex_unlock(&table->philos[i].philo_mutex);
		}
		ft_usleep(2000);
	}
}