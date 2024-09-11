/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:15:56 by edouard           #+#    #+#             */
/*   Updated: 2024/09/11 17:14:53 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	clean_exit(t_table *table)
{
	int		i;
	char	*sem_name;
	char	*id_str;

	i = 0;
	while (i < table->nb_philo)
	{
		id_str = ft_itoa(table->philos[i].id);
		sem_name = ft_strjoin("/philo_sem_", id_str);
		free(id_str);
		sem_close(table->philos[i].philo_sem);
		sem_unlink(sem_name);
		free(sem_name);
		i++;
	}
	sem_close(table->forks_sem);
	sem_close(table->write_sem);
	sem_close(table->dead_sem);
	if (table->philos)
		free(table->philos);
	exit(0);
}

void	finish_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		kill(table->philos[i].pid, SIGKILL);
		i++;
	}
	clean_exit(table);
}
