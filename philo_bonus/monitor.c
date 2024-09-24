/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:13:29 by edouard           #+#    #+#             */
/*   Updated: 2024/09/24 17:32:06 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void monitor_philosophers(t_table *table) {
    while (!table->dead) {
        for (int i = 0; i < table->nb_philo; i++) {
            sem_wait(table->dead_sem);
            long time_since_last_meal = get_current_time_in_ms() - table->philos[i].last_meal;
            printf("time since last meal: %ld\n", time_since_last_meal);
            printf("time to die: %ld\n", table->time_to_die);
            if (time_since_last_meal > table->time_to_die) {
               write_status(&table->philos[i], "died");
                table->dead = true;
                for (int j = 0; j < table->nb_philo; j++)
                    kill(table->philos[j].pid, SIGTERM);
                sem_post(table->dead_sem);
                return;
            }
            sem_post(table->dead_sem);
        }
    }
}
