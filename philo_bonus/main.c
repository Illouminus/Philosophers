/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:06:39 by edouard           #+#    #+#             */
/*   Updated: 2024/09/11 18:36:06 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (argc == 5 || argc == 6)
	{
		if (parse_args(&table, argv) != 0)
			return (error_handler("Error parsing arguments"));
		if (data_init(&table) != 0)
			return (error_handler("Error initializing data"));
		sem_wait(table.dead_sem);
		if (table.nb_limit_meals != -1 && table.nb_philo != 1)
		{
			i = 0;
			while (i < table.nb_philo)
			{
				sem_wait(table.full_philos_sem);
				i++;
			}
		}
		finish_simulation(&table);
	}
	else
		return (error_handler("Invalid numbers of arguments"));
	return (0);
}
