/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:46:47 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/17 09:29:11 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_cycle(void *ptr)
{
	int		min_eat;
	t_philo	*philo;

	philo = (t_philo *) ptr;
	min_eat = philo->data->must_eat;
	while (philo->data->end == false))
	{
		philo_take_fork(philo);
		philo_eat(philo);
		if (philo->eat_cnt >= min_eat && min_eat > 0)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
