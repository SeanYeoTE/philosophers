/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:34:59 by seayeo            #+#    #+#             */
/*   Updated: 2024/07/18 12:57:08 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

bool	all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_num)
{
	bool	ret;

	ret = false;
	safe_mutex_handlle(mutex, LOCK);
	if (*threads == philo_num)
		ret = true;
	safe_mutex_handlle(mutex, UNLOCK);
	return (ret);
}

void	increase_long(pthread_mutex_t *mutex, long *target)
{
	safe_mutex_handlle(mutex, LOCK);
	(*target)++;
	safe_mutex_handlle(mutex, UNLOCK);
}

void	de_synchronize_philos(t_philo *philo)
{
	if (philo->table->num_philos  % 2 == 0)
	{
		if (philo->id % 2 == 0)
		{
			precise_usleep(3e4, philo->table);
		}
	}
	else
	{
		if (philo->id % 2)
		{
			thinking(philo, true);
		}
	}
}