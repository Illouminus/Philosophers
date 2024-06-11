/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:07:06 by edouard           #+#    #+#             */
/*   Updated: 2024/06/11 16:49:03 by edouard          ###   ########.fr       */
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
#include <errno.h>

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
	bool is_full;
	long last_meal;
	t_fork *left_fork;
	t_fork *right_fork;
	pthread_t thread_id;
	t_mutex philo_mutex;
	t_table *table;
} t_philo;

/*
** ANSI Escape Sequences for Bold Text Colors
** Usage:
**     printf(R "This is red text." RST);
**     printf(B "This is blue text." RST);
** Remember to use RST to reset the color after setting it.
*/

#define DEBUG_MODE 0
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
} t_opcode;

typedef enum e_time_code
{
	SECONDS,
	MILLISECOND,
	MICROSECOND,
} t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
} t_philo_status;

#define RST "\033[0m"	 /* Reset to default color */
#define RED "\033[1;31m" /* Bold Red */
#define G "\033[1;32m"	 /* Bold Green */
#define Y "\033[1;33m"	 /* Bold Yellow */
#define B "\033[1;34m"	 /* Bold Blue */
#define M "\033[1;35m"	 /* Bold Magenta */
#define C "\033[1;36m"	 /* Bold Cyan */
#define W "\033[1;37m"	 /* Bold White */

struct s_table
{
	long nb_philo;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long nb_limit_meals;
	long start_time;
	bool is_dead;
	bool all_threads_ready;
	t_mutex table_mutex;
	t_mutex write_mutex;
	t_philo *philos;
	t_fork *forks;
};

void error_exit(const char *str);
void parse_args(t_table *table, char **argv);
void *safe_malloc(size_t size);
void safe_thread_handler(pthread_t *thread, void *(*start)(void *), void *data, t_opcode opcode);
void safe_mutex_handler(t_mutex *mutex, t_opcode opcode);
void data_init(t_table *table);

void wait_for_all_threads(t_table *table);
long gettime(int time_code);
void write_status(t_philo_status status, t_philo *philo, bool debug);
void ft_usleep(long time, t_table *table);

void set_bool(t_mutex *mutex, bool *dest, bool value);
bool get_bool(t_mutex *mutex, bool *src);
void set_long(t_mutex *mutex, long *dest, bool value);
long get_long(t_mutex *mutex, long *src);
bool simulation_finished(t_table *table);

void start_dinner(t_table *table);

#endif