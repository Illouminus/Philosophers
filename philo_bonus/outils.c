/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:35:59 by edouard           #+#    #+#             */
/*   Updated: 2024/07/14 22:12:51 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

unsigned int gettime(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

static void *monitoring(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->death);

		if (philo->next_meal < (unsigned int)gettime())
		{
			write_status(DIED, philo);
			sem_post(philo->data->stop);
			break;
		}
		sem_post(philo->data->death);
		sem_wait(philo->data->death);
		if (philo->data->eat_counter != -1 && philo->is_full)
		{
			write_status(FULL, philo);
			sem_post(philo->data->stop);
			break;
		}
		sem_post(philo->data->death);
		usleep(1000);
	}
	return (NULL);
}

static void dinner_simulation(t_philo *philo)
{
	pthread_t death;

	philo->next_meal = gettime() + (unsigned int)philo->data->time_to_die;
	pthread_create(&death, NULL, monitoring, philo);
	pthread_detach(death);
	while (1)
	{
		philo_take_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		write_status(THINKING, philo);
	}
}

void create_process(t_table *table, t_philo *philo)
{
	int i;

	i = 0;
	while (i < table->philo_numbers)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			dinner_simulation(philo + i);
			exit(0);
		}
		i++;
		usleep(100);
	}
}
