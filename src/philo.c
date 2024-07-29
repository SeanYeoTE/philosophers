/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:50:24 by seayeo            #+#    #+#             */
/*   Updated: 2024/07/29 13:17:43 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(void)
{
	struct timeval	time;
	long			ms;

	if (gettimeofday(&time, NULL))
		write_error("Error: gettimeofday failed");
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	return (ms);
}

void	write_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int main(int argc, char **argv)
{
	t_data data;

	if (argc != 5 && argc != 6)
		write_error("Error: Invalid number of arguments");
	else
	{
		check_input(argv, &data);
		init_data(&data);
		simulation(&data);
	}
	
}