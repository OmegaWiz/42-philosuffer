/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 08:48:29 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/17 08:55:32 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	if (is_starve(philo, now))
		return ;
	philo_print(philo, SLEEP, now);
	usleep(philo->data->sleep_time * 1000);
}
