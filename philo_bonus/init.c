/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:29:46 by edouard           #+#    #+#             */
/*   Updated: 2024/08/28 12:05:24 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void single_philosopher_simulation(t_philo *philo)
{
	sem_wait(philo->table->forks);
	write_status(philo, "has taken a fork");
	ft_usleep(philo->table->time_to_die);
	write_status(philo, "died");
	sem_post(philo->table->forks);
}

static int init_forks(sem_t **forks, int nb_philo)
{
	*forks = sem_open("/forks_sem", O_CREAT | O_EXCL, 0644, nb_philo);
	if (*forks == SEM_FAILED)
	{
		sem_unlink("/forks_sem");
		*forks = sem_open("/forks_sem", O_CREAT | O_EXCL, 0644, nb_philo);
		if (*forks == SEM_FAILED)
			return error_handler("initializing fork semaphore");
	}
	return 0;
}

static void init_philosophers(t_philo *philos, t_table *table)
{
	int i = 0;
	table->full_philos = 0;
	table->start_time = get_current_time_in_ms();
	while (i < table->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].nb_meals = 0;
		philos[i].is_full = false;
		philos[i].last_meal = get_current_time_in_ms();
		philos[i].table = table;
		i++;
	}
}

static int create_philosopher_processes(t_philo *philos, int nb_philo)
{
	int i = 0;
	while (i < nb_philo)
	{
		philos[i].pid = fork();
		if (philos[i].pid < 0)
			return error_handler("creating process for philosopher");
		if (philos[i].pid == 0)
		{
			philosopher_routine(&philos[i]);
			exit(0);
		}
		i++;
	}
	return 0;
}

int data_init(t_table *table)
{
	if (init_forks(&table->forks, table->nb_philo) != 0)
		return 1;
	table->write_sem = sem_open("/write_sem", O_CREAT, 0644, 1);
	if (table->write_sem == SEM_FAILED)
		return error_handler("initializing write semaphore");
	table->dead_sem = sem_open("/dead_sem", O_CREAT, 0644, 1);
	if (table->dead_sem == SEM_FAILED)
		return error_handler("initializing dead semaphore");
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		return error_handler("allocating memory for philosophers");
	init_philosophers(table->philos, table);
	if (table->nb_philo == 1)
	{
		single_philosopher_simulation(&table->philos[0]);
		return 0;
	}
	if (create_philosopher_processes(table->philos, table->nb_philo) != 0)
		return 1;
	return 0;
}