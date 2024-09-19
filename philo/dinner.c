/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:36:56 by edouard           #+#    #+#             */
/*   Updated: 2024/09/19 09:29:14 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void	philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	pthread_mutex_lock(&philo->left_fork->fork);
	write_status(philo, "has taken a fork");
}

static void	philo_put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	write_status(philo, "has put a fork");
}

static void	philo_eat(t_philo *philo)
{
	write_status(philo, "is eating");
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal = get_current_time_in_ms();
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->philo_mutex);
	ft_usleep(philo->table->time_to_eat);
}

static void	philo_sleep(t_philo *philo)
{
	ft_usleep(philo->table->time_to_sleep);
	write_status(philo, "is sleeping");
}

void	*dinner_simulation(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (1)
	{
		if (check_if_philo_is_dead(philo) || check_if_philo_is_full(philo))
			break ;
		philo_take_forks(philo);
		philo_eat(philo);
		philo_put_forks(philo);
		philo_sleep(philo);
		write_status(philo, "is thinking");
		if (check_if_philo_is_dead(philo) || check_if_philo_is_full(philo))
			break ;
	}
	return (NULL);
}
