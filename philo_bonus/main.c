/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:06:39 by edouard           #+#    #+#             */
/*   Updated: 2024/09/19 12:11:56 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (parse_args(&table, argv) != 0)
			return (error_handler("Error parsing arguments"));
		if (data_init(&table) != 0)
			return (error_handler("Error initializing data"));
		monitor_philosophers(&table);
		for (int i = 0; i < table.nb_philo; i++)
			waitpid(table.philos[i].pid, NULL, 0);
		finish_simulation(&table);
	}
	else
		return (error_handler("Invalid numbers of arguments"));
	return (0);
}
