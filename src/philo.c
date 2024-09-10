/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:50:24 by seayeo            #+#    #+#             */
/*   Updated: 2024/09/10 16:46:51 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Safe implementation of atoi to convert string to long
 *
 * This function converts a string to a long integer, checking for overflow.
 *
 * @param str The string to convert
 * @param result Pointer to store the result
 * @return int 1 if conversion was successful, 0 otherwise
 */
int ft_atoi_safe(const char *str, long *result)
{
    long n = 0;
    int sign = 1;
    
    if (*str == '-')
        sign = -1;
    if (*str == '-' || *str == '+')
        str++;
    while (*str && *str >= '0' && *str <= '9')
    {
        n = n * 10 + (*str - '0');
        if (n > INT_MAX || n < INT_MIN)
            return 0;
        str++;
    }
    *result = (long)(n * sign);
    return 1;
}

/**
 * @brief Initialize the shared data structure
 *
 * This function parses command line arguments and initializes the shared data structure.
 *
 * @param data Pointer to the shared data structure
 * @param argc Argument count
 * @param argv Array of argument strings
 * @return int 1 if initialization was successful, 0 otherwise
 */
int	initialize_data(t_data *data, int argc, char **argv)
{
	if (!ft_atoi_safe(argv[1], &data->num_philosophers) ||
        !ft_atoi_safe(argv[2], &data->time_to_die) ||
        !ft_atoi_safe(argv[3], &data->time_to_eat) ||
        !ft_atoi_safe(argv[4], &data->time_to_sleep))
        return 0;
	if (argc == 6 && !ft_atoi_safe(argv[5], &data->max_meals))
        return 0;
	else if (argc == 5)
		data->max_meals = -1;
    pthread_mutex_init(&data->start_mutex, NULL);
    set_bool(&data->start_mutex, &data->end_simulation, false);
    set_long(&data->start_mutex, &data->ready_count, 0);
    set_bool(&data->start_mutex, &data->start_flag, false);

    
    return 1;
}

/**
 * @brief Main function for the dining philosophers problem
 *
 * This function initializes the simulation, creates philosopher threads,
 * starts the monitor thread, and cleans up resources at the end.
 *
 * @param argc Argument count
 * @param argv Array of argument strings
 * @return int 0 if successful, 1 if an error occurred
 */
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep\
			[number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	if (!initialize_data(&data, argc, argv))
	{
		printf("Error: Invalid input\n");
		return (1);
	}
	if (data.num_philosophers <= 0)
	{
		printf("Error: number_of_philosophers must be greater than 0\n");
		return (1);
	}
	initialize_forks(&data);

	pthread_t monitor_thread;
    pthread_create(&monitor_thread, NULL, monitor_routine, &data);
	
	create_philosopher_threads(&data);

	
	join_philosopher_threads(&data);
	set_bool(&data.start_mutex, &data.end_simulation, true);
	pthread_join(monitor_thread, NULL);
	
	destroy_mutexes(&data);
	return (0);
}
