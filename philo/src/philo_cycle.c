/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:42:21 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/20 15:22:16 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo)
{
	long long	now;

	now = get_timerell(philo->data->start, philo->now);
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->no_print == true)
	{
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	printf(BBLU"%lld ms"RESET, now / 1000);
	printf(BYEL" %d "RESET, philo->id);
	if (philo->status == EAT)
		printf(RED"is eating\n"RESET);
	else if (philo->status == SLEEP)
		printf(CYN"is sleeping\n"RESET);
	else if (philo->status == THINK)
		printf("is thinking\n");
	else if (philo->status == THINK_I || philo->status == THINK_U)
		printf(GRN"has taken a fork\n"RESET);
	else if (philo->status == DEAD)
	{
		printf(BHYEL"died\n"RESET);
		philo->data->no_print = true;
	}
	pthread_mutex_unlock(&philo->data->print);
}

void	philo_think(t_philo *philo, bool is_mine)
{
	if (is_mine == true)
	{
		philo->status = THINK;
		print_status(philo);
		philo->status = THINK_I;
		pthread_mutex_lock(&philo->data->forks[philo->lfork]);
	}
	else if (philo->data->philo_cnt > 1)
		pthread_mutex_lock(&philo->data->forks[philo->rfork]);
	else
		bomb(philo);
	philo->now = get_timeval();
	if (is_dead(philo) == true)
	{
		if (is_mine == false)
			pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
		return ;
	}
	print_status(philo);
	philo->status++;
}

void	philo_eat(t_philo *philo)
{
	print_status(philo);
	philo->last_eat = philo->now;
	while (is_dead(philo) == false && get_timerell(philo->last_eat, philo->now)
		< philo->data->time_to_eat)
	{
		usleep(philo->data->lag_time);
		philo->now = get_timeval();
	}
	philo->eat_cnt++;
	if (philo->eat_cnt == philo->data->eat_cnt)
		philo->data->full_cnt++;
	pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->data->forks[philo->rfork]);
	philo->status = SLEEP;
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo);
	philo->last_sleep = philo->now;
	while (is_dead(philo) == false
		&& get_timerell(philo->last_sleep, philo->now)
		< philo->data->time_to_sleep)
	{
		usleep(philo->data->lag_time);
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
