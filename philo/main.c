/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:06:39 by edouard           #+#    #+#             */
/*   Updated: 2024/08/22 12:00:35 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int main(int argc, char **argv)
{
	t_table table;

	if (argc == 5 || argc == 6)
	{
		if (parse_args(&table, argv) != 0)
		{
			printf("Error parsing arguments.\n");
			return 1;
		}
		// data_init(&table);
		// start_dinner(&table);
		// clean_exit(&table);
	}
	else
	{
		printf("Invalid numbers of arguments \n");
		return 1;
	}
	return (0);
}
