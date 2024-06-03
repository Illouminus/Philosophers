/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:30:47 by edouard           #+#    #+#             */
/*   Updated: 2024/06/03 14:50:19 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void *safe_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
		error_exit("Malloc failed\n");
	return (ptr);
}

static void handle_mutex_error(int status, t_opcode opcode)
{
	if (0 == status)
		return;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode || DESTROY == opcode))
		error_exit("The mutex is not initialized\n");
	else if (EINVAL == status && INIT == opcode)
		error_exit("The mutex is already initialized\n");
	else if (EDEADLK == status)
		error_exit("A deadlock would occurend if the thread blocked waiting for mutex\n");
	else if (EPERM == status)
		error_exit("The current thread does not own the mutex\n");
	else if (ENOMEM == status)
		error_exit("Insufficient memory exists to initialize the mutex\n");
	else if (EBUSY == status)
		error_exit("The mutex is already locked\n");
	else
		error_exit("An error occured\n");
}

void safe_mutex_handler(t_mutex *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else
		error_exit("Invalid opcode\n");
}