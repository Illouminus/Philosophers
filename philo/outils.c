/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:26:27 by edouard           #+#    #+#             */
/*   Updated: 2024/07/12 16:10:38 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

long	gettime(int time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (MILLISECOND == time_code)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (MICROSECOND == time_code)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else if (SECONDS == time_code)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else
		error_exit("Wrong input to gettime:");
	return (1337);
}

void	ft_usleep(long time, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < time)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = time - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
			while (gettime(MICROSECOND) - start < time)
				;
	}
}

void	clean_exit(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->nb_philo)
	{
		philo = table->philos + i;
		safe_mutex_handler(&philo->philo_mutex, DESTROY);
	}

	safe_mutex_handler(&table->table_mutex, DESTROY);
	safe_mutex_handler(&table->write_mutex, DESTROY);
	free(table->philos);
	free(table->forks);
}

void	error_exit(const char *str)
{
	printf(RED " %s\n" RST, str);
	exit(EXIT_FAILURE);
}
