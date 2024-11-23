/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:53:14 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/23 21:13:44 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	spinlock(&philo->table->start_flag, &philo->table->table_data);
	desync_start(philo->id);
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*solo(void *arg)
{
	t_philo    *philo;

	philo = (t_philo *)arg;
}

int	is_philo_dead(t_philo *philo)
{
	long	time;

	time = get_time(1);
	if (time - philo->last_meal > philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%ld %ld died\n", time - philo->table->start_time, philo->id + 1);
		pthread_mutex_unlock(&philo->table->print);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_table	*table;
	long	i;
	long	time;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->num_philos)
		{
			time = get_time(1);
			if (time - table->philos[i].last_meal > table->time_to_die)
			{
				pthread_mutex_lock(&table->print);
				printf("%ld %ld died\n", time - table->start_time, i + 1);
				pthread_mutex_unlock(&table->print);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
