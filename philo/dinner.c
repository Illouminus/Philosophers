/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:36:56 by edouard           #+#    #+#             */
/*   Updated: 2024/08/24 11:40:59 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void philo_take_forks(t_philo *philo)
{
	if (philo->left_fork->fork_id > philo->right_fork->fork_id)
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		pthread_mutex_lock(&philo->left_fork->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		pthread_mutex_lock(&philo->right_fork->fork);
	}
	write_status(philo, "has taken a fork");
}

static void philo_put_forks(t_philo *philo)
{
	if (philo->left_fork->fork_id > philo->right_fork->fork_id)
	{
		pthread_mutex_unlock(&philo->left_fork->fork);
		pthread_mutex_unlock(&philo->right_fork->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->right_fork->fork);
		pthread_mutex_unlock(&philo->left_fork->fork);
	}
	write_status(philo, "has put a fork");
}

static void philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal = get_current_time_in_ms();
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->philo_mutex);

	write_status(philo, "is eating");
	ft_usleep(philo->table->time_to_eat); // Выполняем usleep после обновления данных
}

static void philo_sleep(t_philo *philo)
{
	ft_usleep(philo->table->time_to_sleep);
	write_status(philo, "is sleeping");
}

void *dinner_simulation(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(10); // Небольшая задержка для равномерного начала

	while (1)
	{
		pthread_mutex_lock(&philo->table->dead_mutex);
		if (philo->table->is_dead)
		{
			pthread_mutex_unlock(&philo->table->dead_mutex);
			break; // Выход из цикла, если симуляция завершена
		}
		pthread_mutex_unlock(&philo->table->dead_mutex);

		philo_take_forks(philo);
		philo_eat(philo);
		philo_put_forks(philo);

		pthread_mutex_lock(&philo->table->dead_mutex);
		if (philo->table->is_dead)
		{
			pthread_mutex_unlock(&philo->table->dead_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->table->dead_mutex);

		philo_sleep(philo);
		write_status(philo, "is thinking");
	}
	return NULL;
}
