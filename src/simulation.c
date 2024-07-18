/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:22:32 by seayeo            #+#    #+#             */
/*   Updated: 2024/07/18 12:52:01 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* if no meals, retrun  0
if only one philo, seperate function
create all threads and philos
create monitoring thread
 */

void    thinking(t_philo *philo, bool pre_simulation)
{
    long    t_eat;
    long    t_sleep;
    long    t_think;
    
    if (!pre_simulation)
        write_status(THINKING, philo, DEBUG_MODE);
    if (philo->table->num_philos % 2 == 0)
        return ;
    t_eat = philo->table->time_to_eat;
    t_sleep = philo->table->time_to_sleep;
    t_think = t_eat * 2 - t_sleep;
    if (t_think < 0)
        t_think = 0;
    precise_usleep(t_think *0.4, philo->table);
    
}

void    *lone_philo(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    wait_all_threads(philo->table);
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
    increase_long(&philo->table->table_mutex, &philo->table->threads_running_number);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    while (!simulation_finished(philo->table))
    {
        usleep(200);
    }
    return (NULL);
}
// eat : write eat, update last meal and update meal counter
// update bool full, release forks
static  void    eat(t_philo *philo)
{
    safe_mutex_handlle(&philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
    safe_mutex_handlle(&philo->second_fork->fork, LOCK);
    write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
    
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
    philo->meals_counter++;
    write_status(EATING, philo, DEBUG_MODE);
    precise_usleep(philo->table->time_to_eat, philo->table);
    if (philo->table->num_meals > 0 && philo->meals_counter == philo->table->num_meals)
        set_bool(&philo->philo_mutex, &philo->full, true);

    safe_mutex_handlle(&philo->first_fork->fork, UNLOCK);
    safe_mutex_handlle(&philo->second_fork->fork, UNLOCK);
}

void    *dinner_simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;

    // wait for all threads to be ready
    wait_all_threads(philo->table);

    // set last meal time
    set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));

    
    increase_long(&philo->table->table_mutex, &philo->table->threads_running_number);

    // set last meal time
    while (!simulation_finished(philo->table))
    {
        // think am i full
        if (get_bool(&philo->philo_mutex, &philo->full))
            break ;
        // eating
        eat(philo);
        
        // sleep-> write status ->
        write_status(SLEEPING, philo, DEBUG_MODE);
        precise_usleep(philo->table->time_to_sleep, philo->table);
        // thinking
        thinking(philo, false);
    }
    return (NULL);    
}

void    dinner_start(t_table *table)
{
    int i;

    i = -1;
    if (table->num_meals == 0)
        return ;
    else if (table->num_philos == 1)
        safe_thread_handle(&table->philos[0].thread, lone_philo, &table->philos[0], CREATE);
    else
    {
        while (++i < table->num_philos)
            safe_thread_handle(&table->philos[i].thread, dinner_simulation, &table->philos[i], CREATE);
    }
    // monitoring thread
    safe_thread_handle(&table->monitor_thread, monitor_dinner, table, CREATE);

    // start of simulation
    table->start_time = gettime(MILLISECOND);
    
    set_bool(&table->table_mutex, &table->all_threads_ready, true);
    
    i = -1;
    while (++i < table->num_philos)
        safe_thread_handle(&table->philos[i].thread, NULL, NULL, JOIN);
    // all philos are full here
    set_bool(&table->table_mutex, &table->end_simulation, true);

    safe_thread_handle(&table->monitor_thread, NULL, NULL, JOIN);
}