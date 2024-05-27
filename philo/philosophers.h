/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:07:06 by edouard           #+#    #+#             */
/*   Updated: 2024/05/27 20:17:05 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>

typedef pthread_mutex_t t_mutex;
typedef struct s_table t_table;
typedef struct s_fork
{
	t_mutex fork;
	int fork_id;
} t_fork;

typedef struct s_philo
{
	int id;
	int nb_meals;
	bool is_full;
	long last_meal;
	t_fork *left_fork;
	t_fork *right_fork;
	pthread_t thread_id;
	t_table *table;
} t_philo;

struct s_table
{
	long nb_philo;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long nb_limit_meals;
	long start_time;
	bool is_dead;
	t_philo *philos;
	t_fork *forks;
	t_mutex print_mutex;
	t_mutex death_mutex;
};

#endif