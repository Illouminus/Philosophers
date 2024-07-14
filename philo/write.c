/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:18:15 by edouard           #+#    #+#             */
/*   Updated: 2024/07/14 17:02:43 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void write_status_debug(t_philo_status status, t_philo *philo,
										 long elapsed)
{
	if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
		printf(W "%6ld" RST " %d has taken the 1° fork 🍽"
					"\t\t\tn°" B "[🍴 %d 🍴]\n" RST,
				 elapsed,
				 philo->id,
				 philo->left_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && !simulation_finished(philo->table))
		printf(W "%6ld" RST " %d has taken the 2° fork 🍽"
					"\t\t\tn°" B "[🍴 %d 🍴]\n" RST,
				 elapsed,
				 philo->id,
				 philo->right_fork->fork_id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf(W "%6ld" C " %d is eating 🍝"
					"\t\t\t" Y "[🍝 %ld 🍝]\n" RST,
				 elapsed,
				 philo->id,
				 philo->nb_meals);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf(W "%6ld" RST " %d is sleeping 😴\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf(W "%6ld" RST " %d is thinking 🤔\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED "\t\t💀💀💀 %6ld %d died   💀💀💀\n" RST, elapsed, philo->id);
}

void write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_time;
	if (get_bool(&philo->philo_mutex, &philo->is_full))
		return;
	safe_mutex_handler(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status) && !simulation_finished(philo->table))
			printf(W "%-6ld" RST " %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf(W "%-6ld" C " %d is eating\n" RST, elapsed, philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf(W "%-6ld" RST " %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && !simulation_finished(philo->table))
			printf(W "%-6ld" RST " %d is thinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf(RED "%-6ld %d died\n" RST, elapsed, philo->id);
	}
	safe_mutex_handler(&philo->table->write_mutex, UNLOCK);
}
