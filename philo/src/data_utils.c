/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 20:16:37 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/20 08:40:52 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_init(t_data *data, int argc, char **argv)
{
	int	i;

	data->philo_cnt = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_cnt = ft_atoi(argv[5]);
	else
		data->eat_cnt = -1;
	data->end_cnt = 0;
	data->is_dead = false;
	data->start = get_time();
	data->forks = malloc(sizeof(t_mutex) * data->philo_cnt);
	if (!data->forks)
		philo_error(NULL, NULL, MALLOC_ERROR, 0);
	i = -1;
	while (++i < data->philo_cnt)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->print, NULL);
	data->philo = philo_init(data, argc, argv);
	if (!data->philo)
		philo_error(data, NULL, MALLOC_ERROR, 0);
}
