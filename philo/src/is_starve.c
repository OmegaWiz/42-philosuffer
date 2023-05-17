/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_starve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 08:18:35 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/17 08:22:29 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_starve(t_philo *philo, t_timeval now)
{
	long	diff;

	diff = time_subtract(&now, &philo->last_eat);
	if (diff > philo->data->die_time)
	{
		philo_print(philo, DIE, now);
		philo->data->end = true;
		return (true);
	}
	return (false);
}

long	time_subtract(t_timeval *now, t_timeval *last)
{
	long	sec;
	long	usec;

	sec = now->tv_sec - last->tv_sec;
	usec = now->tv_usec - last->tv_usec;
	return (sec * 1000 + usec / 1000);
}
