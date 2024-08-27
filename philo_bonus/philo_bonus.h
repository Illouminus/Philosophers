/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:07:06 by edouard           #+#    #+#             */
/*   Updated: 2024/08/27 16:18:20 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <signal.h>

#ifndef PHILO_MAX
#define PHILO_MAX 200
#endif

typedef struct s_table t_table;

typedef struct s_philo
{
	int id;
	long nb_meals;
	bool is_full;
	long last_meal;
	pid_t pid; // Используется для хранения ID процесса философа
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
	int full_philos;
	sem_t *forks;
	sem_t *write_sem;
	sem_t *dead_sem;
	t_philo *philos;
};

/********************PARSING********************************/
int parse_args(t_table *table, char **argv);
bool is_digit(char c);
bool is_space(char c);
const char *check_sign(const char *str, int *error);
const char *skip_spaces(const char *str);
const char *check_digits(const char *str, int *error);
const char *valid_input(const char *str, int *error);

/********************UTILS********************************/
void ft_usleep(long ms);
int error_handler(const char *message);
long get_current_time_in_ms(void);
void write_status(t_philo *philo, const char *status);

/********************INIT********************************/
int data_init(t_table *table);

/********************PHILO********************************/
int check_if_philo_is_dead_bonus(t_philo *philo);
void monitor_processes(t_table *table);
void clean_exit(t_table *table);
void philosopher_routine(t_philo *philo);
#endif