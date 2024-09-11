/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:06:39 by edouard           #+#    #+#             */
/*   Updated: 2024/09/11 14:33:18 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	single_philosopher_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	write_status(philo, "has taken a fork");
	ft_usleep(philo->table->time_to_die);
	write_status(philo, "died");
	pthread_mutex_unlock(&philo->left_fork->fork);
}

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	monitor;

	if (argc == 5 || argc == 6)
	{
		if (parse_args(&table, argv) != 0)
			return (error_handler("Error parsing arguments\n"));
		if (data_init(&table) != 0)
			return (error_handler("Error initializing data\n"));
		if (table.nb_philo != 1)
		{
			if (create_philosopher_threads(table.philos, table.nb_philo) != 0)
				return (1);
			if (pthread_create(&monitor, NULL, (void *)monitoring, &table) != 0)
				return (error_handler("Error creating monitoring thread\n"));
			pthread_join(monitor, NULL);
		}
	}
	else
		return (error_handler("Wrong number of arguments\n"));
	clean_exit(&table);
	return (0);
}
