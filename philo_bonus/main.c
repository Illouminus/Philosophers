/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:06:39 by edouard           #+#    #+#             */
/*   Updated: 2024/08/27 17:04:47 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

#include <stdio.h>

void print_data(t_table *table)
{
	printf("Simulation Data:\n");
	printf("Number of Philosophers: %ld\n", table->nb_philo);
	printf("Time to Die: %ld ms\n", table->time_to_die);
	printf("Time to Eat: %ld ms\n", table->time_to_eat);
	printf("Time to Sleep: %ld ms\n", table->time_to_sleep);
	if (table->nb_limit_meals != -1)
		printf("Number of Meals Limit: %ld\n", table->nb_limit_meals);
	else
		printf("Number of Meals Limit: No limit\n");

	printf("\nForks Info:\n");
	for (int i = 0; i < table->nb_philo; i++)
	{
		printf("Fork %d: Initialized\n", i + 1);
	}

	printf("\nPhilosophers Info:\n");
	for (int i = 0; i < table->nb_philo; i++)
	{
		printf("Philosopher %d:\n", table->philos[i].id);
		printf("\tMeals Eaten: %ld\n", table->philos[i].nb_meals);
		printf("\tLast Meal Time: %ld ms\n", table->philos[i].last_meal);
		printf("\tIs Full: %s\n", table->philos[i].is_full ? "Yes" : "No");
	}
	printf("\nInitialization completed successfully.\n");
}

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
		if (data_init(&table) != 0)
		{
			printf("Error initializing data\n");
			return 1;
		}
		// print_data(&table);
		if (table.nb_philo != 1)
			monitor_processes(&table);
	}
	else
	{
		printf("Invalid numbers of arguments \n");
		return 1;
	}
	return (0);
}
