/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:42:39 by edouard           #+#    #+#             */
/*   Updated: 2024/08/27 17:10:52 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void philosopher_eat(t_philo *philo)
{
	write_status(philo, "is eating");

	philo->last_meal = get_current_time_in_ms();
	ft_usleep(philo->table->time_to_eat);

	philo->nb_meals++;
	if (philo->table->nb_limit_meals != -1 && philo->nb_meals >= philo->table->nb_limit_meals)
	{
		philo->is_full = true;
		exit(0);
	}
}
void philosopher_take_forks(t_philo *philo)
{
	sem_wait(philo->table->forks);
	write_status(philo, "has taken a fork");
	sem_wait(philo->table->forks);
	write_status(philo, "has taken a fork");
}

void philosopher_put_forks(t_philo *philo)
{
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
	write_status(philo, "has put down forks");
}

void philosopher_sleep(t_philo *philo)
{
	write_status(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

void philosopher_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (1)
	{
		if (check_if_philo_is_dead_bonus(philo))
			break;
		philosopher_take_forks(philo);
		philosopher_eat(philo);
		philosopher_put_forks(philo);
		if (check_if_philo_is_dead_bonus(philo))
			break;
		write_status(philo, "is thinking");
		philosopher_sleep(philo);
	}
	exit(0);
}