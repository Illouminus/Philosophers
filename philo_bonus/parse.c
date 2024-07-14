/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 09:58:02 by edouard           #+#    #+#             */
/*   Updated: 2024/07/14 21:28:32 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

int ft_error_put(t_table *table, char *message, int ret)
{
	if (table)
	{
		if (table->forks)
			free(table->forks);
	}
	printf("%s\n", message);
	return (ret);
}

int ft_set_rest(t_table *table, int num, int i)
{
	if (i == 4)
	{
		if (num < 60)
			return (ft_error_put(table,
										"Error: THE time_to_sleep CAN'T BE LESS THAN 60 ms", 1));
		table->time_to_sleep = num;
	}
	else if (i == 5)
	{
		if (num == 0)
			table->eat_counter = -1;
		else
		{
			table->eat_counter = num;
			table->current_eat = 0;
			table->max_eat = num * table->philo_numbers;
		}
	}
	return (0);
}

int ft_set_data(t_table *table, int num, int i)
{
	if (i == 1)
	{
		if (num == 0)
			return (ft_error_put(NULL,
										"Error: NO PHELOSOPHER IN THE TABILE", 1));
		table->philo_numbers = num;
	}
	else if (i == 2)
	{
		if (num < 60)
			return (ft_error_put(table,
										"Error: THE time_to_die CAN'T BE LESS THAN 60 ms", 1));
		table->time_to_die = num;
	}
	else if (i == 3)
	{
		if (num < 60)
			return (ft_error_put(table,
										"Error: THE time_to_eat CAN'T BE LESS THAN 60 ms", 1));
		table->time_to_eat = num;
	}
	else
		ft_set_rest(table, num, i);
	return (0);
}

int ft_get_number(char *arg)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while (arg[i])
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			num = num * 10 + (arg[i] - '0');
		else
			return (ft_error_put(NULL, "Error: Number Only", -1));
		i++;
	}
	return (num);
}

int ft_parsing(char **av, t_table *table)
{
	int num;
	int i;

	i = 1;
	while (av[i])
	{
		num = ft_get_number(av[i]);
		if (num == -1)
			return (1);
		if (ft_set_data(table, num, i))
			return (1);
		i++;
	}
	if (i == 5)
	{
		table->eat_counter = -1;
		table->current_eat = -1;
		table->max_eat = -1;
	}
	return (0);
}