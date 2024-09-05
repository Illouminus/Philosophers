/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:13:29 by edouard           #+#    #+#             */
/*   Updated: 2024/09/05 16:36:48 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void monitor_processes(t_table *table)
{
	int i;

	i = 0;
	while (i < table->nb_philo)
	{
		kill(table->philos[i].pid, SIGKILL);
		i++;
	}
	clean_exit(table);
}

void *check_death(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while (1)
	{
		if (philo->next_meal < get_current_time_in_ms())
		{
			printf("Current time: %ld\n", get_current_time_in_ms());
			printf("Last meal + time to die: %ld\n", philo->last_meal + philo->table->time_to_die);
			write_status(philo, "died");
			sem_post(philo->table->dead_sem);
			break;
		}
		// ft_usleep(1000);
	}
	return NULL;
}