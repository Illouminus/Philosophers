/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:14:23 by edouard           #+#    #+#             */
/*   Updated: 2024/08/27 11:42:49 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool check_philosopher_death(t_philo *philo)
{
	bool has_died = false;

	pthread_mutex_lock(&philo->philo_mutex);

	if (get_current_time_in_ms() - philo->last_meal > philo->table->time_to_die && !philo->is_full)
	{
		write_status(philo, "died");
		pthread_mutex_lock(&philo->table->dead_mutex);
		philo->table->is_dead = true;
		pthread_mutex_unlock(&philo->table->dead_mutex);
		has_died = true;
	}

	pthread_mutex_unlock(&philo->philo_mutex);

	return has_died;
}

void monitoring(t_table *table)
{
	int i;
	while (1)
	{
		i = 0;

		while (i < table->nb_philo)
		{
			if (check_philosopher_death(&table->philos[i]))
				return;
			pthread_mutex_lock(&table->philos[i].philo_mutex);
			if (table->philos[i].is_full)
				table->full_philos++;
			pthread_mutex_unlock(&table->philos[i].philo_mutex);
			i++;
		}

		if (table->full_philos == table->nb_philo)
			return;

		ft_usleep(2000);
	}
}