/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:27:24 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/20 09:06:24 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_data	data;
	int		i;

	data_init(&data, argc, argv);
	i = -1;
	while (++i < data.philo_cnt)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_cycle, &philo[i]))
			philo_error(&philo, NULL, THREAD_ERROR, 0);
	}
	i = -1;
	while (++i < data.philo_cnt)
	{
		if (pthread_join(philo[i].thread, NULL))
			philo_error(&philo, NULL, THREAD_ERROR, 0);
	}
	philo_free(&philo, &data);
	return (0);
}
