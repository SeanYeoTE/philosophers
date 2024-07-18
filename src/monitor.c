/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:38:22 by seayeo            #+#    #+#             */
/*   Updated: 2024/07/18 12:00:59 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static  bool    philo_died(t_philo *philo)
{
    long    elapsed;
    long    t_to_die;

    if (get_bool(&philo->philo_mutex, &philo->full))
        return (false);
    
    elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
    t_to_die = philo->table->time_to_die / 1000;

    if (elapsed > t_to_die)
        return (true);
    return (false);
}
void    *monitor_dinner(void *data)
{
    int     i;
    t_table *table;

    table = (t_table *)data;

    // make sure all philo running
    while (!all_threads_running(&table->table_mutex, &table->threads_running_number, table->num_philos))
        ;
    while(!simulation_finished(table))
    {
        i = -1;
        while (++i < table->num_philos && !simulation_finished(table))
        {
            if (philo_died(&table->philos[i]))
            {   
                set_bool(&table->table_mutex, &table->end_simulation, true);
                write_status(DIED, &table->philos[i], DEBUG_MODE);
            }
        }
    }
    return (NULL);
}