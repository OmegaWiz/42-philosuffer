/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_take_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 08:29:31 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/17 08:39:31 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_fork(t_philo *philo)
{
	int			left;
	int			right;
	t_timeval	tv;

	left = (philo->id - 1 + philo->data->philo_cnt) % philo->data->philo_cnt;
	right = (philo->id + philo->data->philo_cnt) % philo->data->philo_cnt;
	pthread_mutex_lock(&philo->data->fork[left]);
	gettimeofday(&tv, NULL);
	if (is_starve(philo, tv) == true)
		return ;
	philo_print(philo, FORK, tv);
	pthread_mutex_lock(&philo->data->fork[right]);
	gettimeofday(&tv, NULL);
	if (is_starve(philo, tv) == true)
		return ;
	philo_print(philo, FORK, tv);
	pthread_mutex_unlock(&philo->data->fork[left]);
	pthread_mutex_unlock(&philo->data->fork[right]);
}
