/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 20:16:37 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/20 09:39:18 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	arg_init(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		philo_error(NULL, "wrong number of arguments", ARG_ERROR, 0);
	data->philo_cnt = ft_atoi(argv[1]);
	if (data->philo_cnt < 2 || data->philo_cnt > 200)
		philo_error(NULL, "number_of_philo is not in range", ARG_ERROR, 0);
	data->time_to_die = ft_atoi(argv[2]);
	if (data->time_to_die < 60)
		philo_error(NULL, "time_to_die is not in range", ARG_ERROR, 0);
	data->time_to_eat = ft_atoi(argv[3]);
	if (data->time_to_eat < 60)
		philo_error(NULL, "time_to_eat is not in range", ARG_ERROR, 0);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_sleep < 60)
		philo_error(NULL, "time_to_sleep is not in range", ARG_ERROR, 0);
	if (argc == 6)
	{
		data->eat_cnt = ft_atoi(argv[5]);
		if (data->eat_cnt < 1)
			philo_error(NULL, "number_of_times_each_philo_must_eat
			 is not in range", ARG_ERROR, 0);
	}
	else
		data->eat_cnt = -1;
}

void	data_init(t_data *data, int argc, char **argv)
{
	int	i;

	arg_init(data, argc, argv);
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

t_data	*data_free(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_cnt)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->print);
	free(data->forks);
	data->philo(data->philo);
	return (NULL);
}
