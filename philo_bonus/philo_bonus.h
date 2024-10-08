/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:07:06 by edouard           #+#    #+#             */
/*   Updated: 2024/09/24 18:07:52 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef PHILO_MAX
#  define PHILO_MAX 200
# endif

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	long				nb_meals;
	long				last_meal;
	long				next_meal;
	pid_t				pid;
	t_table				*table;
}						t_philo;

struct					s_table
{
	long				nb_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nb_limit_meals;
	long				start_time;
	bool				dead;
	sem_t				*forks_sem;
	sem_t				*write_sem;
	sem_t				*dead_sem;
	t_philo				*philos;
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
long					get_current_time_in_ms(void);
void					write_status(t_philo *philo, const char *status);

/********************INIT********************************/
int						data_init(t_table *table);

/********************PHILO********************************/
void					finish_simulation(t_table *table);
void					clean_exit(t_table *table);
void					philosopher_routine(t_philo *philo);
int						create_philosopher_processes(t_philo *philos,
							int nb_philo);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_itoa(int n);
void					monitor_philosophers(t_table *table);
#endif