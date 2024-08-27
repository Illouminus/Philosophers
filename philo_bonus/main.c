/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:06:39 by edouard           #+#    #+#             */
/*   Updated: 2024/08/27 14:15:46 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

int main(int argc, char **argv)
{
	t_table table;

	if (argc == 5 || argc == 6)
	{
		if (parse_args(&table, argv) != 0)
		{
			printf("Error parsing arguments\n");
			return 1;
		}
		// if (data_init(&table) != 0)
		// {
		// 	printf("Error initializing data\n");
		// 	return 1;
		// }
		// if (table.nb_philo != 1)
		// 	monitoring(&table);
		// clean_exit(&table);
	}
	else
	{
		printf("Invalid numbers of arguments \n");
		return 1;
	}
	return (0);
}
