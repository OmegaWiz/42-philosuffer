/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:04:23 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/17 09:27:03 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	if (is_starve(philo, now))
		return ;
	philo_print(philo, EAT, now);
	philo->last_eat = now;
	usleep(philo->data->eat_time * 1000);
	philo->eat_cnt++;
}
