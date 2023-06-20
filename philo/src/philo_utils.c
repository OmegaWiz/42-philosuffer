/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 20:24:09 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/20 15:22:33 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_init(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * data->philo_cnt);
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < data->philo_cnt)
	{
		philo[i].id = i + 1;
		philo[i].eat_cnt = 0;
		philo[i].status = THINK_I;
		philo[i].last_eat = data->start;
		philo[i].last_sleep = data->start;
		philo[i].now = data->start;
		philo[i].lfork = i;
		philo[i].rfork = (i + 1) % data->philo_cnt;
		philo[i].data = data;
	}
	return (philo);
}

t_philo	*philo_free(t_philo *philo)
{
	if (philo)
		free(philo);
	return (NULL);
}
