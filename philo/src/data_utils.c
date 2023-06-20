/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 20:16:37 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/20 15:40:25 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	arg_init(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		data_error(NULL, "wrong number of arguments", ARG_ERROR, 0);
	data->philo_cnt = ft_atou_warn(argv[1]);
	if (data->philo_cnt < 1 || data->philo_cnt > 200)
		data_error(NULL, "number_of_philo is not in range", ARG_ERROR, 0);
	data->time_to_die = ft_atou_warn(argv[2]) * (long long) 1000;
	if (data->time_to_die < 60000)
		data_error(NULL, "time_to_die is not in range", ARG_ERROR, 0);
	data->time_to_eat = ft_atou_warn(argv[3]) * (long long) 1000;
	if (data->time_to_eat < 60000)
		data_error(NULL, "time_to_eat is not in range", ARG_ERROR, 0);
	data->time_to_sleep = ft_atou_warn(argv[4]) * (long long) 1000;
	if (data->time_to_sleep < 60000)
		data_error(NULL, "time_to_sleep is not in range", ARG_ERROR, 0);
	if (argc == 6)
	{
		data->eat_cnt = ft_atou_warn(argv[5]);
		if (data->eat_cnt < 1)
			data_error(NULL, "number_eat is not in range", ARG_ERROR, 0);
	}
	else
		data->eat_cnt = -1;
}

void	data_init(t_data *data, int argc, char **argv)
{
	int	i;

	arg_init(data, argc, argv);
	data->full_cnt = 0;
	data->is_dead = false;
	data->no_print = false;
	data->start = get_timeval();
	data->lag_time = 5 * data->philo_cnt;
	data->forks = malloc(sizeof(t_mutex) * data->philo_cnt);
	if (!data->forks)
		data_error(NULL, NULL, MALLOC_ERROR, 0);
	i = -1;
	while (++i < data->philo_cnt)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->print, NULL);
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
	return (NULL);
}
