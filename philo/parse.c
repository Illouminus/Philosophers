/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:46:44 by edouard           #+#    #+#             */
/*   Updated: 2024/06/03 14:04:38 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static inline bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static const char *valid_input(const char *str)
{
	int len;
	const char *nmb;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_exit("Only positive value \n");
	if (!is_digit(*str))
		error_exit("The input in not a correct digit\n");
	nmb = str;
	while (is_digit(*str))
	{
		len++;
		str++;
	}
	if (len > 10)
		error_exit("The number is too big\n");
	return (nmb);
}

static long ft_atol(const char *str)
{
	long nb;

	nb = 0;
	str = valid_input(str);
	while (is_digit(*str))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	if (nb > INT_MAX)
		error_exit("The number is too big\n");
	return (nb);
}

void parse_args(t_table *table, char **argv)
{
	table->nb_philo = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
}