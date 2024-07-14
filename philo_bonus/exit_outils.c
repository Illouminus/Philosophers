/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:26:50 by edouard           #+#    #+#             */
/*   Updated: 2024/07/14 21:13:32 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void clean_exit(t_table *table, t_philo *philo)
{
	int i;

	i = 0;
	while (i < table->philo_numbers)
		kill(philo[i++].pid, SIGKILL);
	sem_close(table->death);
	sem_close(table->message);
	sem_close(table->stop);
	sem_close(table->forks);
	free(philo);
}

void parsing_exit(const char *message)
{
	if (message)
		perror(message);
	exit(EXIT_FAILURE);
}
