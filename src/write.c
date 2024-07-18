/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:41:15 by seayeo            #+#    #+#             */
/*   Updated: 2024/07/18 12:45:15 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// writing has to be thread safe
// need to lock again
static	void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
		printf("%-6ld %d has taken a fork %d\n", elapsed, philo->id, philo->first_fork->id);
	else if (TAKE_SECOND_FORK == status && !simulation_finished(philo->table))
		printf("%-6ld %d has taken a fork %d\n", elapsed, philo->id, philo->second_fork->id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf("%-6ld %d is eating      MEAL: %ld\n", elapsed, philo->id, philo->meals_counter);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf("%-6ld %d died\n", elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;
	
	elapsed = gettime(MILLISECOND) - philo->table->start_time;
	
	if (philo->full)
		return ;
	
	safe_mutex_handlle(&philo->table->write_lock, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
		&& !simulation_finished(philo->table))
			printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf("%-6ld %d is eating\n", elapsed, philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf("%-6ld %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && !simulation_finished(philo->table))
			printf("%-6ld %d is thinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf("%-6ld %d died\n", elapsed, philo->id);
	}
   
	
	safe_mutex_handlle(&philo->table->write_lock, UNLOCK);
}