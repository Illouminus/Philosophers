/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:29:46 by edouard           #+#    #+#             */
/*   Updated: 2024/09/11 18:49:48 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

int	single_philosopher_simulation(t_philo *philo)
{
	sem_wait(philo->table->forks_sem);
	write_status(philo, "has taken a fork");
	ft_usleep(philo->table->time_to_die);
	write_status(philo, "died");
	sem_post(philo->table->forks_sem);
	clean_exit(philo->table);
	return (0);
}

static int	init_semaphores(t_table *table)
{
	sem_unlink("/write_sem");
	sem_unlink("/dead_sem");
	sem_unlink("/forks_sem");
	sem_unlink("/full_philos_sem");
	sem_unlink("/block_dead");
	table->write_sem = sem_open("/write_sem", O_CREAT, 0644, 1);
	table->block_dead = sem_open("/block_dead", O_CREAT, 0644, 1);
	table->dead_sem = sem_open("/dead_sem", O_CREAT, 0644, 0);
	table->full_philos_sem = sem_open("/full_philos_sem", O_CREAT, 0644, 0);
	table->forks_sem = sem_open("/forks_sem", O_CREAT, 0644, table->nb_philo);
	if (table->write_sem == SEM_FAILED || table->dead_sem == SEM_FAILED
		|| table->forks_sem == SEM_FAILED || table->full_philos_sem == SEM_FAILED
		|| table->block_dead == SEM_FAILED)
		return (error_handler("initializing semaphores"));
	return (0);
}

static void	init_philosophers(t_philo *philos, t_table *table)
{
	int		i;
	char	*sem_name;
	char	*id_str;

	i = 0;
	table->start_time = get_current_time_in_ms();
	table->dead = false;
	while (i < table->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].nb_meals = 0;
		philos[i].table = table;
		id_str = ft_itoa(philos[i].id);
		sem_name = ft_strjoin("/philo_sem_", id_str);
		free(id_str);
		sem_unlink(sem_name);
		philos[i].philo_sem = sem_open(sem_name, O_CREAT, 0644, 1);
		free(sem_name);
		if (philos[i].philo_sem == SEM_FAILED)
			error_handler("initializing semaphores");
		i++;
	}
}

static int	create_philosopher_processes(t_philo *philos, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		philos[i].pid = fork();
		if (philos[i].pid < 0)
			return (error_handler("creating process for philosopher"));
		if (philos[i].pid == 0)
			philosopher_routine(&philos[i]);
		i++;
		ft_usleep(100);
	}
	return (0);
}

int	data_init(t_table *table)
{
	if (init_semaphores(table) != 0)
		return (1);
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		return (error_handler("allocating memory for philosophers"));
	init_philosophers(table->philos, table);
	if (table->nb_philo == 1)
		return (single_philosopher_simulation(&table->philos[0]));
	return (create_philosopher_processes(table->philos, table->nb_philo));
}
