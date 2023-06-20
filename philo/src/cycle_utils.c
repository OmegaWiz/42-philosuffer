/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:23:31 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/20 15:20:54 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	bomb(t_philo *philo)
{
	while (is_dead(philo) == false)
	{
		usleep(philo->data->lag_time);
		philo->now = get_timeval();
	}
}

long long	get_timerell(t_timeval start, t_timeval end)
{
	long long	time;

	time = (end.tv_sec - start.tv_sec) * 1000000;
	time += (end.tv_usec - start.tv_usec);
	return (time);
}

t_timeval	get_timeval(void)
{
	t_timeval		timeval;

	gettimeofday(&timeval, NULL);
	return (timeval);
}

bool	set_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead);
	data->is_dead = true;
	pthread_mutex_unlock(&data->dead);
	return (true);
}

bool	is_dead(t_philo *philo)
{
	if (philo->data->is_dead == true)
		return (true);
	if (get_timerell(philo->last_eat, philo->now) > philo->data->time_to_die)
	{
		philo->status = DEAD;
		print_status(philo);
		return (set_dead(philo->data));
	}
	if (philo->data->full_cnt == philo->data->philo_cnt)
	{
		return (set_dead(philo->data));
	}
	return (false);
}
