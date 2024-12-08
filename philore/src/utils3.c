/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:44:45 by seayeo            #+#    #+#             */
/*   Updated: 2024/12/08 17:45:19 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dead_do_this(t_table *table, long i, long time)
{
	set_bool(&table->philos[i].mutex, &table->philos[i].dead, true);
	set_bool(&table->table_data, &table->end_sim, true);
	print_state_change(&table->philos[i], "died", time);
	return ;
}

bool	all_philo_full(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->num_philos)
	{
		if (!get_bool(&table->philos[i].mutex, &table->philos[i].full))
			return (false);
	}
	return (true);
}
