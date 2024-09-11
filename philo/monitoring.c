/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:14:23 by edouard           #+#    #+#             */
/*   Updated: 2024/09/11 14:53:37 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_philosopher_death(t_philo *philo)
{
	bool	has_died;

	has_died = false;
	pthread_mutex_lock(&philo->philo_mutex);
	if (get_current_time_in_ms() - philo->last_meal > philo->table->time_to_die
		&& !philo->is_full)
	{
		write_status(philo, "died");
		pthread_mutex_lock(&philo->table->dead_mutex);
		philo->table->is_dead = true; 
		pthread_mutex_unlock(&philo->table->dead_mutex);
		has_died = true;
	}
	pthread_mutex_unlock(&philo->philo_mutex);
	return (has_died);
}

bool	check_philosopher_full(t_philo *philo)
{
	bool	is_full;

	is_full = false;
	pthread_mutex_lock(&philo->table->full_mutex);
	if (philo->table->full_philos == philo->table->nb_philo)
	{
		is_full = true;
		pthread_mutex_lock(&philo->table->dead_mutex);
		philo->table->is_dead = true;
		pthread_mutex_unlock(&philo->table->dead_mutex);
		pthread_mutex_unlock(&philo->table->full_mutex);

	}
	pthread_mutex_unlock(&philo->table->full_mutex);
	return (is_full);
}

void	monitoring(t_table *table)
{
	int i;
	while (1)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			if (check_philosopher_death(&table->philos[i]))
				return ; 
			if (check_philosopher_full(&table->philos[i]))
				return ;
			i++;
		}
	}
}
