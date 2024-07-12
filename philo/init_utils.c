/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaillot <ebaillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:30:47 by edouard           #+#    #+#             */
/*   Updated: 2024/07/12 17:26:50 by ebaillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error_exit("Malloc failed\n");
	return (ptr);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		error_exit("The value specified by mutex is invalid");
	else if (EINVAL == status && INIT == opcode)
		error_exit("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur if the thread ");
	else if (EPERM == status)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		error_exit("The process cannot allocate enough memory");
	else if (EBUSY == status)
		error_exit("Mutex is locked");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("The thread is not joinable\n");
	else if (EAGAIN == status)
		error_exit("The system lacked the necessary resources\n");
	else if (ESRCH == status)
		error_exit("No thread could be found corresponding\n");
	else if (EINVAL == status && CREATE == opcode)
		error_exit("The thread is already initialized\n");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur\n");
}

void safe_mutex_handler(t_mutex *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
	{
		usleep(10);
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	}
	else if (UNLOCK == opcode)
	{
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	}
	else if (INIT == opcode)
	{
		usleep(10);
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	}
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for mutex_handle:");
}


void	safe_thread_handler(pthread_t *thread, void *(*foo)(void *), void *data,
		t_opcode opcode)
{
	if (CREATE == opcode)
	{
		usleep(10);
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	}
	else if (JOIN == opcode)
	{
		usleep(10);
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	}
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread_handle:");
}
