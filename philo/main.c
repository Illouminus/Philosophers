/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:06:39 by edouard           #+#    #+#             */
/*   Updated: 2024/08/23 16:47:37 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

#include <stdio.h>

void print_initialized_values(t_table *table)
{
	printf("Table Info:\n");
	printf("Number of Philosophers: %ld\n", table->nb_philo);
	printf("Time to Die: %ld\n", table->time_to_die);
	printf("Time to Eat: %ld\n", table->time_to_eat);
	printf("Time to Sleep: %ld\n", table->time_to_sleep);
	printf("Meal Limit: %ld\n", table->nb_limit_meals);
	printf("Start Time: %ld\n", table->start_time);
	printf("Is Dead: %s\n", table->is_dead ? "Yes" : "No");

	printf("\nMutex Info:\n");
	printf("Write Mutex: %p\n", (void *)&table->write_mutex);
	printf("Dead Mutex: %p\n", (void *)&table->dead_mutex);

	printf("\nForks Info:\n");
	for (int i = 0; i < table->nb_philo; i++)
	{
		printf("Fork %d - Mutex: %p, Fork ID: %d\n",
				 i + 1, (void *)&table->forks[i].fork, table->forks[i].fork_id);
	}

	printf("\nPhilosophers Info:\n");
	for (int i = 0; i < table->nb_philo; i++)
	{
		printf("Philosopher %d:\n", i + 1);
		printf("\tID: %d\n", table->philos[i].id);
		printf("\tNumber of Meals: %ld\n", table->philos[i].nb_meals);
		printf("\tLast Meal Time: %ld\n", table->philos[i].last_meal);
		printf("\tLeft Fork ID: %d\n", table->philos[i].left_fork->fork_id);
		printf("\tRight Fork ID: %d\n", table->philos[i].right_fork->fork_id);
		printf("\tThread ID: %p\n", (void *)table->philos[i].thread_id);
		printf("\tPhilosopher Mutex: %p\n", (void *)&table->philos[i].philo_mutex);
	}
}

int main(int argc, char **argv)
{
	t_table table;

	if (argc == 5 || argc == 6)
	{
		if (parse_args(&table, argv) != 0)
			error_handler("Error parsing arguments");
		if (data_init(&table) != 0)
			error_handler("Error initializing data");
		print_initialized_values(&table);
		// start_dinner(&table);
		clean_exit(&table);
	}
	else
	{
		printf("Invalid numbers of arguments \n");
		return 1;
	}
	return (0);
}
