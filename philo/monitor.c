/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:41:07 by edouard           #+#    #+#             */
/*   Updated: 2024/06/12 16:42:38 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void *monitor_simulation(void *data)
{
	t_table *table;
	table = (t_table *)data;
	while (!all_threads_running(table))
		usleep(1000);

	return (NULL);
}