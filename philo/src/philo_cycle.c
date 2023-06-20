/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:42:21 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/20 12:00:49 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo)
{
	long	now;

	now = get_timerel(philo->data->start, philo->now);
	pthread_mutex_lock(&philo->data->print);
	if (philo->status == EAT)
		printf("%ld %d is eating\n", now, philo->id);
	else if (philo->status == SLEEP)
		printf("%ld %d is sleeping\n", now, philo->id);
	else if (philo->status == THINK)
		printf("%ld %d is thinking\n", now, philo->id);
	else if (philo->status == THINK_I || philo->status == THINK_U)
		printf("%ld %d has taken a fork\n", now, philo->id);
	else if (philo->status == DEAD)
		printf("%ld %d died\n", now, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void	philo_think(t_philo *philo, bool is_mine)
{
	if (is_mine == true)
	{
		philo->status = THINK;
		print_status(philo);
		pthread_mutex_lock(&philo->data->fork[philo->lfork]);
	}
	else
		pthread_mutex_lock(&philo->data->fork[philo->rfork]);
	philo->now = get_timeval();
	if (is_dead(philo) == true)
	{
		if (is_mine == false)
			pthread_mutex_unlock(&philo->data->fork[philo->lfork]);
		return ;
	}
	print_status(philo);
	if (is_mine == true)
		philo->status = THINK_U;
	else
		philo->status = EAT;
}

void	philo_eat(t_philo *philo)
{
	print_status(philo);
	philo->last_eat = philo->now;
	while (is_dead(philo) == false && get_timerel(philo->last_eat, philo->now)
		< philo->data->time_to_eat)
	{
		usleep(10000);
		philo->now = get_timeval();
	}
	pthread_mutex_unlock(&philo->data->fork[philo->lfork]);
	pthread_mutex_unlock(&philo->data->fork[philo->rfork]);
	philo->status = SLEEP;
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEP);
	philo->last_sleep = philo->now;
	while (is_dead(philo) == false && get_timerel(philo->last_sleep, philo->now)
		< philo->data->time_to_sleep)
	{
		usleep(10000);
		philo->now = get_timeval();
	}
	philo->status = THINK_I;
}

void	*philo_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (is_dead(philo) == false)
	{
		if (philo->status == THINK_I)
			philo_think(philo, true);
		else if (philo->status == THINK_U)
			philo_think(philo, false);
		else if (philo->status == EAT)
			philo_eat(philo);
		else if (philo->status == SLEEP)
			philo_sleep(philo);
	}
	return (NULL);
}
