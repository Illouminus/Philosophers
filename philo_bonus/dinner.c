/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:42:39 by edouard           #+#    #+#             */
/*   Updated: 2024/09/24 18:37:20 by ebaillot         ###   ########.fr       */
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

void	*monitor_philosopher(void *philo_void)
{
	t_philo	*philo;
	long	current_time;

	philo = (t_philo *)philo_void;
	while (!philo->table->dead)
	{
		current_time = get_current_time_in_ms();
		if (current_time - philo->last_meal > philo->table->time_to_die)
		{
			write_status(philo, "died");
			philo->table->dead = true;
			sem_post(philo->table->dead_sem);
			return (NULL);
		}
		ft_usleep(1); // Немного увеличьте время для стабильности
	}
	return (NULL);
}

void	philosopher_routine(t_philo *philo)
{
	pthread_t	monitor_thread;


	philo->last_meal = get_current_time_in_ms();
	pthread_create(&monitor_thread, NULL, monitor_philosopher, philo);
	pthread_detach(monitor_thread);
	
	while (!philo->table->dead)
	{
		philosopher_take_forks(philo);
		philosopher_eat(philo);
		philosopher_put_forks(philo);
		philosopher_sleep(philo);
		write_status(philo, "is thinking");
	}
}
