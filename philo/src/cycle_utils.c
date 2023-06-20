/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:23:31 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/20 11:28:57 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_timerel(t_timeval start, t_timeval end)
{
	return ((end.tv_sec - start.tv_sec) * 1000
			+ (end.tv_usec - start.tv_usec) / 1000);
}

t_timeval	get_timeval(int time)
{
	t_timeval		timeval;

	gettimeofday(&timeval, NULL);
	return (timeval);
}

bool	set_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead);
	philo->dead = true;
	pthread_mutex_unlock(&data->dead);
	return (true);
}

bool	is_dead(t_philo *philo)
{
	if (philo->dead == true)
		return (true);
	if (get_timerel(philo->last_eat, philo->now) > philo->data->time_to_die)
	{
		philo->status = DEAD;
		print_status(philo);
		return (set_dead(philo->data)));
	}
	if (philo->data->full_cnt == philo->data->philo_cnt)
	{
		if (COLOR == 1)
		{
			pthread_mutex_lock(&philo->data->print);
			printf("All philosophers are full\n");
			pthread_mutex_unlock(&philo->data->print);
		}
		return (set_dead(philo->data));
	}
	return (false);
}
