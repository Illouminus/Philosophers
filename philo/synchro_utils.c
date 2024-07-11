/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:29:17 by edouard           #+#    #+#             */
/*   Updated: 2024/07/11 14:12:43 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	wait_for_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

bool	all_threads_running(t_mutex *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex_handler(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handler(mutex, UNLOCK);
	return (ret);
}

void	increase_long(t_mutex *mutex, long *value)
{
	safe_mutex_handler(mutex, LOCK);
	(*value)++;
	safe_mutex_handler(mutex, UNLOCK);
}

void	de_sync_philos(t_philo *philo)
{
	if (philo->table->nb_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2 == 0)
			thinking(philo, true);
	}
}
