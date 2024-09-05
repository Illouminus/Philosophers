/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:42:39 by edouard           #+#    #+#             */
/*   Updated: 2024/09/05 16:42:10 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void philosopher_eat(t_philo *philo)
{
	write_status(philo, "is eating");
	usleep(philo->table->time_to_eat * 1000);
	philo->last_meal = get_current_time_in_ms();
	philo->next_meal = philo->last_meal + philo->table->time_to_die;
	// philo->nb_meals++;
}
void philosopher_take_forks(t_philo *philo)
{
	sem_wait(philo->table->forks_sem);
	write_status(philo, "has taken a fork");
	sem_wait(philo->table->forks_sem);
	write_status(philo, "has taken a fork");
}

void philosopher_put_forks(t_philo *philo)
{
	sem_post(philo->table->forks_sem);
	sem_post(philo->table->forks_sem);
	write_status(philo, "has put down forks");
}

void philosopher_sleep(t_philo *philo)
{
	write_status(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
}

void philosopher_routine(t_philo *philo)
{
	pthread_t philo_thread;

	philo->next_meal = get_current_time_in_ms() + philo->table->time_to_die;
	pthread_create(&philo_thread, NULL, check_death, philo);
	pthread_detach(philo_thread);
	while (1)
	{
		philosopher_take_forks(philo);
		philosopher_eat(philo);
		philosopher_put_forks(philo);
		philosopher_sleep(philo);
		write_status(philo, "is thinking");
	}
}