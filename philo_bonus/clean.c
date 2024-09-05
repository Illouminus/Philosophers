/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:15:56 by edouard           #+#    #+#             */
/*   Updated: 2024/09/05 15:49:38 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void clean_exit(t_table *table)
{
	printf("Cleaning up\n");
	sem_close(table->forks_sem);
	sem_close(table->write_sem);
	sem_close(table->dead_sem);
	if (table->philos)
		free(table->philos);
	// exit(0);
}