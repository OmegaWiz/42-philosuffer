/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:33:28 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/16 15:00:08 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_philo **philo, t_data *data, int argc, char **argv)
{
	int	i;

	*philo = NULL;
	if (argc < 5 || argc > 6)
		philo_error(philo, NULL, ARGC_ERROR, 0);
	if (argc == 6)
		data->min_eat = atoi(argv[5]);
	else
		data->min_eat = -1;
	data->philo_cnt = atoi(argv[1]);
	data->die_time = atoi(argv[2]);
	data->eat_time = atoi(argv[3]);
	data->bed_time = atoi(argv[4]);
	data->end = false;
	data->fork = (t_mutex *) malloc_check(sizeof(t_mutex) * data->philo_cnt);
	*philo = (t_philo *) malloc_check(sizeof(t_philo *) * data->philo_cnt);
	i = -1;
	while (++i < data->philo_cnt)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].data = data;
		(*philo)[i].eat_cnt = 0;
		gettimeofday(&(*philo)[i].last_eat, NULL);
		pthread_mutex_init(&data->fork[i], NULL);
	}
}
