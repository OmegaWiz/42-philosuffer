/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:46:47 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/16 15:03:23 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_cycle(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *) ptr;
	while (!philo->data->end)
	{
		philo_take_fork(philo);
		if (philo->data->end)
			break ;
		philo_eat(philo);
		if (philo->data->end)
			break ;
		philo_sleep(philo);
		if (philo->data->end)
			break ;
		philo_think(philo);
	}
	return (NULL);
}
