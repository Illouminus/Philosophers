/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:06:39 by edouard           #+#    #+#             */
/*   Updated: 2024/09/06 10:37:04 by edouard          ###   ########.fr       */
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
			return (error_handler("Error parsing arguments"));
		if (data_init(&table) != 0)
			return (error_handler("Error initializing data"));
		// print_data(&table);
		sem_wait(table.dead_sem);
		sem_wait(table.dead_sem);
		monitor_processes(&table);
	}
	else
		return (error_handler("Invalid numbers of arguments"));
	return (0);
}
