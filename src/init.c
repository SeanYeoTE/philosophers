/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:27:15 by seayeo            #+#    #+#             */
/*   Updated: 2024/07/16 20:51:57 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_init(t_table	*table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->num_philos);
	table->forks = safe_malloc(sizeof(t_fork) * table->num_philos);
	while (++i < table->num_philos)
	{
		safe_mutex_handlle(&table->forks[i].fork, INIT);
		table->forks[i].id = i;
	}
}