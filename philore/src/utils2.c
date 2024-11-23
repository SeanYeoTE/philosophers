/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:45:09 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/23 21:59:11 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	desync_start(long id)
{
	if (id % 2 == 0)
		usleep(100);
}

void	precise_sleep(long time, long current_time, long prev_timestamp)
{
	currtime = get_time(1) - philo->table->start_time;
	while (currtime - prev_timestamp < time)
	{
		usleep(60);
		currtime = get_time(1) - philo->table->start_time;
	}
}

void	print_state_change(t_philo *philo, char *state, long timestamp)
{
	pthread_mutex_lock(&philo->table->print);
	if (get_bool(&philo->table->table_data, &philo->table->end_sim))
		printf("%ld %ld %s\n", timestamp, philo->id + 1, state);
	else if (get_bool(&philo->table->table_data, &philo->table->dead))
		printf("%ld %ld %s\n", timestamp, philo->id + 1, "died");
	pthread_mutex_unlock(&philo->table->print);
}