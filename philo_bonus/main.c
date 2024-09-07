/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:06:39 by edouard           #+#    #+#             */
/*   Updated: 2024/09/07 11:43:59 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

int main(int argc, char **argv)
{
	t_table table;

	if (argc == 5 || argc == 6)
	{
		if (parse_args(&table, argv) != 0)
			return (error_handler("Error parsing arguments"));
		if (data_init(&table) != 0)
			return (error_handler("Error initializing data"));
		sem_wait(table.dead_sem);
		finish_simulation(&table);
	}
	else
		return (error_handler("Invalid numbers of arguments"));
	return (0);
}
