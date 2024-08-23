/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:36:56 by edouard           #+#    #+#             */
/*   Updated: 2024/08/23 17:37:47 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void *dinner_simulation(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	printf("Philosopher %d is alive\n", philo->id);
	return NULL;
}