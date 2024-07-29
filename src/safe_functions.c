/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:46:05 by seayeo            #+#    #+#             */
/*   Updated: 2024/07/26 13:51:38 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *safe_malloc(size_t bytes)
{
    void    *ptr;

    ptr = malloc(bytes);
    if (!ptr)
        write_error("Error: Malloc failed");
    return (ptr);
}

void    safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
    if (opcode == LOCK)
    {
        if (pthread_mutex_lock(mutex))
            write_error("Error: Mutex lock failed");
    }
    else if (opcode == UNLOCK)
    {
        if (pthread_mutex_unlock(mutex))
            write_error("Error: Mutex unlock failed");
    }
    else if (opcode == INIT)
    {
        if (pthread_mutex_init(mutex, NULL))
            write_error("Error: Mutex init failed");
    }
    else if (opcode == DESTROY)
    {
        if (pthread_mutex_destroy(mutex))
            write_error("Error: Mutex destroy failed");
    }
    else
        write_error("Error: Invalid opcode");
}

void    safe_thread_handle(pthread_t *thread, void *(*func)(void *), void *arg, t_opcode opcode)
{
    if (opcode == CREATE)
    {
        if (pthread_create(thread, NULL, func, arg))
            write_error("Error: Thread creation failed");
    }
    else if (opcode == JOIN)
    {
        if (pthread_join(*thread, NULL))
            write_error("Error: Thread join failed");
    }
    else if (opcode == DETACH)
    {
        if (pthread_detach(*thread))
            write_error("Error: Thread detach failed");
    }
    else
        write_error("Error: Invalid opcode");
}