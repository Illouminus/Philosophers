/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:15:56 by edouard           #+#    #+#             */
/*   Updated: 2024/09/24 18:09:02 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"


void kill_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		kill(table->philos[i].pid, SIGKILL);
		i++;
	}
}

void	clean_exit(t_table *table)
{
	sem_close(table->forks_sem);
	sem_close(table->write_sem);
	sem_close(table->dead_sem);
}

void	finish_simulation(t_table *table)
{
	int	i;
	i = 0;
	clean_exit(table);
	kill_philos(table);
	if (table->philos)
		free(table->philos);
	exit(0);
}
