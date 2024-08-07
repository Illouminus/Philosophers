/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:06:39 by edouard           #+#    #+#             */
/*   Updated: 2024/07/14 09:53:53 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int main(int argc, char **argv)
{
	t_table table;

	if (argc == 5 || argc == 6)
	{
		parse_args(&table, argv);
		data_init(&table);
		start_dinner(&table);
		clean_exit(&table);
	}
	else
		error_exit("Invalid number of arguments. \n");
	return (0);
}
