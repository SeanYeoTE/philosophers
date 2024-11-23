/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:09:18 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/23 21:45:31 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	spinlock(bool *start_flag, pthread_mutex_t *table_data)
{
	while (get_bool(table_data, start_flag))
		;
}

void	errormsg(char *s)
{
	printf("%s\n", s);
}

int	ft_atol_assign(const char *str, long *num)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	res = res * sign;
	if (res < INTMIN | res > INTMAX)
		return (1);
	*num = res;
	return (0);
}

int	thread_creation(pthread_t *thread,
	void *(*start_routine)(void *), void *arg)
{
	if (pthread_create(thread, NULL, start_routine, arg) != 0)
	{
		printf("Failed to create philosopher thread");
		return (0);
	}
	return (1);
}
