/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:27:24 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/20 15:16:45 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	main_thread(t_philo *philo, t_data data, int i)
{
	i = 0;
	while (i < data.philo_cnt)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_cycle, &philo[i]))
			philo_error(philo, NULL, THREAD_ERROR, 0);
		i += 2;
	}
	i = 1;
	usleep(100);
	while (i < data.philo_cnt)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_cycle, &philo[i]))
			philo_error(philo, NULL, THREAD_ERROR, 0);
		i += 2;
	}
	i = -1;
	while (++i < data.philo_cnt)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			philo_error(philo, NULL, THREAD_ERROR, 0);
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	data;

	data_init(&data, argc, argv);
	philo = philo_init(&data);
	main_thread(philo, data, 0);
	philo = philo_free(philo);
	data_free(&data);
	return (0);
}
