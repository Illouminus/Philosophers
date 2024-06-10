/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:06:39 by edouard           #+#    #+#             */
/*   Updated: 2024/06/10 15:12:33 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int main(int argc, char **argv)
{

	t_table table;

	if (argc == 5 || argc == 6)
	{
		parse_args(&table, argv);
		data_init(&table);
		start_dinner(&table);
		clean(&table);
	}
	else
		error_exit("Invalid number of arguments. \n" G
					  "Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]" RST);
	return 0;
}