/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:07:06 by edouard           #+#    #+#             */
/*   Updated: 2024/09/24 17:37:19 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mutex				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				nb_meals;
	bool				is_full;
	long				last_meal;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread_id;
	t_mutex				philo_mutex;
	t_table				*table;
}						t_philo;

# ifndef PHILO_MAX
#  define PHILO_MAX 200
# endif

struct					s_table
{
	long				nb_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nb_limit_meals;
	long				start_time;
	bool				is_dead;
	int					full_philos;
	t_mutex				dead_mutex;
	t_mutex				write_mutex;
	t_mutex				full_mutex;
	t_philo				*philos;
	t_fork				*forks;
};

/********************PARSING********************************/
int						parse_args(t_table *table, char **argv);
bool					is_digit(char c);
bool					is_space(char c);
const char				*check_sign(const char *str, int *error);
const char				*skip_spaces(const char *str);
const char				*check_digits(const char *str, int *error);
const char				*valid_input(const char *str, int *error);

/********************UTILS********************************/
void					ft_usleep(long ms);
int						error_handler(const char *message);
void					clean_exit(t_table *table);
long					get_current_time_in_ms(void);

/********************INIT********************************/
int						data_init(t_table *table);
int						create_philosopher_threads(t_philo *philos,
							int nb_philo);

/********************DINNER********************************/
void					*dinner_simulation(void *arg);
void					write_status(t_philo *philo, const char *status);
void					monitoring(t_table *table);
int						check_if_philo_is_dead(t_philo *philo);
void					single_philosopher_simulation(t_philo *philo);
int						check_if_philo_is_full(t_philo *philo);
#endif