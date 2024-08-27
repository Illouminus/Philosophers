/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:15:56 by edouard           #+#    #+#             */
/*   Updated: 2024/08/27 16:16:08 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void clean_exit(t_table *table)
{

	sem_close(table->forks);
	sem_close(table->write_sem);
	sem_close(table->dead_sem);
	sem_unlink("/forks_sem");
	sem_unlink("/write_sem");
	sem_unlink("/dead_sem");

	free(table->philos);
	free(table->forks);
	exit(0);
}