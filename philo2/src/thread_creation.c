/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:33:05 by seayeo            #+#    #+#             */
/*   Updated: 2024/11/11 20:33:52 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
