/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:07:06 by edouard           #+#    #+#             */
/*   Updated: 2024/06/03 14:46:02 by edouard          ###   ########.fr       */
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
	int nb_meals;
	bool is_full;
	long last_meal;
	t_fork *left_fork;
	t_fork *right_fork;
	pthread_t thread_id;
	t_table *table;
} t_philo;

/*
** ANSI Escape Sequences for Bold Text Colors
** Usage:
**     printf(R "This is red text." RST);
**     printf(B "This is blue text." RST);
** Remember to use RST to reset the color after setting it.
*/

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
	t_philo *philos;
	t_fork *forks;
	t_mutex print_mutex;
	t_mutex death_mutex;
};

void error_exit(const char *str);
void parse_args(t_table *table, char **argv);
void *safe_malloc(size_t size);
#endif