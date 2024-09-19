/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:42:39 by edouard           #+#    #+#             */
/*   Updated: 2024/09/19 11:37:19 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	philosopher_eat(t_philo *philo)
{
	philo->last_meal = get_current_time_in_ms();
	if (philo->table->nb_limit_meals != -1)
		philo->nb_meals++;
	write_status(philo, "is eating");
	ft_usleep(philo->table->time_to_eat);
}

void	philosopher_take_forks(t_philo *philo)
{
	sem_wait(philo->table->forks_sem);
	write_status(philo, "has taken a fork");
	sem_wait(philo->table->forks_sem);
	write_status(philo, "has taken a fork");
}

void	philosopher_put_forks(t_philo *philo)
{
	sem_post(philo->table->forks_sem);
	sem_post(philo->table->forks_sem);
	write_status(philo, "has put down forks");
}

void	philosopher_sleep(t_philo *philo)
{
	write_status(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

void	philosopher_routine(t_philo *philo)
{
	philo->last_meal = get_current_time_in_ms();
	while (!philo->table->dead)
	{
		philosopher_take_forks(philo);
		philosopher_eat(philo);
		philosopher_put_forks(philo);
		philosopher_sleep(philo);
		write_status(philo, "is thinking");
	}
}
