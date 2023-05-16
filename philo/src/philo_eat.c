/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:04:23 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/16 15:20:35 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	t_timeval	now;

	gettimeofday(&time, NULL);
	if (is_dead(philo, now))
		return ;
	philo_print(philo, EAT, now);
	philo->eat_cnt++;
	philo->last_eat = now;
	usleep(philo->data->eat_time * 1000);
}
