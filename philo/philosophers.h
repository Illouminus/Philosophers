/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:07:06 by edouard           #+#    #+#             */
/*   Updated: 2024/08/22 11:59:50 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

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
	long nb_meals;
	long last_meal;
	t_fork *left_fork;
	t_fork *right_fork;
	pthread_t thread_id;
	t_mutex philo_mutex;
	t_table *table;
} t_philo;

#ifndef PHILO_MAX
#define PHILO_MAX 200
#endif

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
} t_philo_status;

struct s_table
{
	long nb_philo;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long nb_limit_meals;
	long start_time;
	bool is_dead;
	// long threads_running_number;
	t_mutex write_mutex;
	t_philo *philos;
	t_fork *forks;
};

/********************PARSING********************************/
int parse_args(t_table *table, char **argv);
bool is_digit(char c);
bool is_space(char c);
const char *check_sign(const char *str, int *error);
const char *skip_spaces(const char *str);
const char *check_digits(const char *str, int *error);
const char *valid_input(const char *str, int *error);

#endif