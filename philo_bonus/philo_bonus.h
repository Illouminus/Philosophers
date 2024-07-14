/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 09:44:03 by edouard           #+#    #+#             */
/*   Updated: 2024/07/14 21:52:44 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <semaphore.h>
#include <sys/types.h>
#include <sys/time.h>
#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

typedef struct s_table t_table;

#ifndef PHILO_MAX
#define PHILO_MAX 200
#endif

typedef enum e_time_code
{
	SECONDS,
	MILLISECOND,
	MICROSECOND,
} t_time_code;

#define DEBUG_MODE 0

#define RST "\033[0m"	 /* Reset to default color */
#define RED "\033[1;31m" /* Bold Red */
#define G "\033[1;32m"	 /* Bold Green */
#define Y "\033[1;33m"	 /* Bold Yellow */
#define B "\033[1;34m"	 /* Bold Blue */
#define M "\033[1;35m"	 /* Bold Magenta */
#define C "\033[1;36m"	 /* Bold Cyan */
#define W "\033[1;37m"	 /* Bold White */

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
	FULL
} t_philo_status;

typedef struct s_philo
{
	t_table *data;
	pid_t pid;
	unsigned int eating_time;
	unsigned int next_meal;
	int index;
	int is_dead;
	int eat_counter;
	int is_full;
} t_philo;

struct s_table
{
	sem_t *forks;
	sem_t *message;
	sem_t *death;
	sem_t *stop;
	unsigned int start;
	int philo_numbers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int eat_counter;
	int max_eat;
	int current_eat;
};

void *safe_malloc(size_t size);
unsigned int gettime();
void write_status(t_philo_status status, t_philo *philo);
void parsing_exit(const char *message);
void create_semaphores(t_table *table);
t_philo *philo_init(t_table *table);
void create_process(t_table *table, t_philo *philo);
void philo_take_fork(t_philo *philo);
void philo_eat(t_philo *philo);
void philo_sleep(t_philo *philo);
void clean_exit(t_table *table, t_philo *philo);
int ft_parsing(char **av, t_table *table);
#endif