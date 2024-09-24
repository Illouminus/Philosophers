/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:46:44 by edouard           #+#    #+#             */
/*   Updated: 2024/09/24 17:37:59 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static long	ft_atol(const char *str, int *error)
{
	long	nb;

	nb = 0;
	str = valid_input(str, error);
	if (*error)
		return (0);
	while (is_digit(*str))
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	if (nb > INT_MAX)
	{
		*error = 1;
		return (0);
	}
	return (nb);
}

static int	parse_number_of_philosophers(t_table *table, const char *arg,
		int *error)
{
	table->nb_philo = ft_atol(arg, error);
	if (*error || table->nb_philo > PHILO_MAX)
	{
		printf("Error: Invalid number of philosophers. Max PHILO_MAX=%d.\n",
			PHILO_MAX);
		return (1);
	}
	return (0);
}

static int	parse_time_value(long *time_field, const char *arg, int *error)
{
	*time_field = ft_atol(arg, error);
	if (*error)
	{
		printf("Error: Invalid time value.\n");
		return (1);
	}
	if (*time_field < 60)
	{
		printf("Error: Time value should be greater than 60ms.\n");
		return (1);
	}
	return (0);
}

static int	parse_limit_meals(t_table *table, const char *arg, int *error)
{
	table->nb_limit_meals = ft_atol(arg, error);
	if (*error)
	{
		printf("Error: Invalid number of limit meals.\n");
		return (1);
	}
	return (0);
}

int	parse_args(t_table *table, char **argv)
{
	int	error;

	error = 0;
	if (parse_number_of_philosophers(table, argv[1], &error))
		return (1);
	if (parse_time_value(&table->time_to_die, argv[2], &error))
		return (1);
	if (parse_time_value(&table->time_to_eat, argv[3], &error))
		return (1);
	if (parse_time_value(&table->time_to_sleep, argv[4], &error))
		return (1);
	if (argv[5])
	{
		if (parse_limit_meals(table, argv[5], &error))
			return (1);
	}
	else
	{
		table->nb_limit_meals = -1;
	}
	return (0);
}
