/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:45:09 by seayeo            #+#    #+#             */
/*   Updated: 2024/12/06 14:21:57 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	desync_start(long id)
{
	if (id % 2 == 0)
		usleep(100);
}

long	get_min_interval(long a, long b, long c)
{
	long	min;

	min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	min = 100;
	// printf("min: %ld\n", min);
	return (min);
}

void	precise_sleep(t_philo *philo, long time, long prev_timestamp)
{
	long endingtime;

	endingtime = prev_timestamp + time;
	while (get_time(1) < endingtime)
	{
		usleep(philo->table->interval);
	}
}
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	print_state_change(t_philo *philo, char *state, long timestamp)
{
	pthread_mutex_lock(&philo->table->print);
	timestamp = timestamp / 1000;
	if (!get_bool(&philo->table->table_data, &philo->table->end_sim))
		printf("%ld %ld %s\n", timestamp, philo->id + 1, state);
	
	else if (ft_strcmp(state, "died") == 0 && get_bool(&philo->mutex, &philo->dead))
	{
		printf("%ld %ld %s\n", timestamp, philo->id + 1, state);
	}
	pthread_mutex_unlock(&philo->table->print);
}
