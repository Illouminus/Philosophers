/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 09:59:33 by edouard           #+#    #+#             */
/*   Updated: 2024/07/14 21:53:13 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void create_semaphores(t_table *table)
{
	sem_unlink("death");
	sem_unlink("message");
	sem_unlink("stop");
	sem_unlink("forks");
	table->death = sem_open("death", O_CREAT, 0600, 1);
	table->message = sem_open("message", O_CREAT, 0600, 1);
	table->stop = sem_open("stop", O_CREAT, 0600, 1);
	table->forks = sem_open("forks", O_CREAT, 0600,
									table->philo_numbers);
}

static void each_philo(t_table *table, t_philo *philo, int i)
{
	philo[i].index = i;
	philo[i].is_dead = 0;
	philo[i].data = table;
	philo[i].is_full = 0;
	philo[i].pid = -1;
	if (table->eat_counter == -1)
		philo[i].eat_counter = -1;
	else
		philo[i].eat_counter = table->eat_counter;
}

t_philo *philo_init(t_table *table)
{
	t_philo *philo;
	int i;

	i = -1;
	philo = malloc(sizeof(t_philo) * table->philo_numbers);
	table->death = NULL;
	table->stop = NULL;
	table->message = NULL;
	table->forks = NULL;
	while (++i < table->philo_numbers)
		each_philo(table, philo, i);
	return (philo);
}
