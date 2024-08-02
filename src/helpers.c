/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:54:07 by seayeo            #+#    #+#             */
/*   Updated: 2024/08/02 18:11:10 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool    simulation_finished(t_data *data)
{
    if (data->max_eat == 0)
        return (false);
    if (data->threads_running == 0)
        return (true);
    return (false);
}

long    get_long(pthread_mutex_t mutex, long *src)
{
    long    ret;

    safe_mutex_handle(&mutex, LOCK);
    ret = *src;
    safe_mutex_handle(&mutex, UNLOCK);
    return (ret);
}

void    set_bool(pthread_mutex_t mutex, bool *dest, bool value)
{
    safe_mutex_handle(&mutex, LOCK);
    *dest = value;
    safe_mutex_handle(&mutex, UNLOCK);
}

bool    get_bool(pthread_mutex_t mutex, bool *src)
{
    bool    ret;

    safe_mutex_handle(&mutex, LOCK);
    ret = *src;
    safe_mutex_handle(&mutex, UNLOCK);
    return (ret);
}

void    set_long_nl(long *dest, long value)
{
    *dest = value;
}

void    set_long(pthread_mutex_t *mutex, long *dest, long value)
{
    safe_mutex_handle(mutex, LOCK);
    *dest = value;
    safe_mutex_handle(mutex, UNLOCK);
}

void    print_status(t_philo *philo, char *status)
{
    long    time;
    puts("print_status");
    time = gettime() - philo->data->start_time;
    safe_mutex_handle(&philo->data->write_mutex, LOCK);
    printf("%ld %d %s\n", time, philo->id + 1, status);
    safe_mutex_handle(&philo->data->write_mutex, UNLOCK);
}