/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 09:51:19 by edouard           #+#    #+#             */
/*   Updated: 2024/07/14 22:21:47 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

int main(int ac, char **av)
{
	t_table table;
	t_philo *philo;

	if (ac == 5 || ac == 6)
	{
		if (ft_parsing(av, &table))
			return (1);
		philo = philo_init(&table);
		table.start = gettime();
		create_semaphores(&table);
		sem_wait(table.stop);
		create_process(&table, philo);
		sem_wait(table.stop);
		clean_exit(&table, philo);
	}
	else
		printf("Error: Too many arguments\n");
	return (0);
}
