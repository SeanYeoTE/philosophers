/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:14:43 by seayeo            #+#    #+#             */
/*   Updated: 2024/07/18 12:05:51 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->num_philos)
	{
		philo = &table->philos[i];
		safe_mutex_handlle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handlle(&table->table_mutex, DESTROY);
	safe_mutex_handlle(&table->write_lock, DESTROY);
	free(table->forks);
	free(table->philos);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	 while (gettime(MICROSECOND) - start < usec)
	 {
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;

		if (rem > 1000)
			usleep(rem / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	 }
}

long	gettime(t_time_code timecode)
{
	struct	timeval	time;
	
	if (gettimeofday(&time, NULL) == -1)
		error_exit("gettimeofday failed");
	else if (timecode == SECOND)
		return (time.tv_sec + (time.tv_usec / 1e6));
	else if (timecode == MILLISECOND)
		return (time.tv_sec * 1000 + time.tv_usec / 1000);
	else if (timecode == MICROSECOND)
		return (time.tv_sec * 1000000 + time.tv_usec);
	else
		error_exit("Invalid timecode");
	return (1337);
}

void	error_exit(const char *msg)
{
	printf("Error: %s\n", msg);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_table	table;
	
	if (argc != 5 && argc != 6)
		error_exit("Invalid number of arguments");
	else
	{
		input_check(&table, argv);
		
		data_init(&table);
		
		dinner_start(&table);

		cleanup(&table);
	}
}