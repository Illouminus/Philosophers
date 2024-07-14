/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:03:20 by edouard           #+#    #+#             */
/*   Updated: 2024/07/14 21:25:06 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void *safe_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
		parsing_exit("Malloc failed\n");
	return (ptr);
}
