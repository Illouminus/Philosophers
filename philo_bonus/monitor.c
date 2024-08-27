/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:13:29 by edouard           #+#    #+#             */
/*   Updated: 2024/08/27 16:23:40 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void monitor_processes(t_table *table)
{
	int status;
	pid_t pid;

	while ((pid = waitpid(-1, &status, 0)) > 0)
	{
		if (WIFEXITED(status) || WIFSIGNALED(status))
		{
			sem_wait(table->dead_sem);
			for (int i = 0; i < table->nb_philo; i++)
			{
				kill(table->philos[i].pid, SIGKILL);
			}
			break;
		}
	}
	clean_exit(table);
}