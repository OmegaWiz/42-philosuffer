/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 08:45:12 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/20 09:37:16 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_instruction(void)
{
	ft_putendl_fd("Usage: ./philo {number_of_philosophers} {time_to_die}
	{time_to_eat} {time_to_sleep} [number_of_times_each_philosopher_must_eat]\n
	{number_of_philosophers} (int: 1-60) - The number of philosophers and also
	 the number of forks.\n
	{time_to_die} (int: >=200) - If a philosopher didn't start eating
	{time_to_die} milliseconds since the beginning of their last meal or the
	 beginning of the simulation, they die.\n
	{time_to_eat} (int: >= 200) - The time in milliseconds it takes for a
	 philosopher to eat. During that time, they will need to hold two forks.\n
	{time_to_sleep} (int: >= 200) - The time in milliseconds the philosopher
	 will spend sleeping.\n
	[number_of_times_each_philosopher_must_eat] (int >= 200) - If all
	 philosophers have eaten at least [number_of_times_each_philosopher_
	must_eat] times, the simulation stops. If not specified, the simulation
	 stops when a philosopher dies\n", 2);
}

void	philo_error(t_data *data, char *str, t_error error, int errnum)
{
	ft_putstr_fd("philo: ", 2);
	if (err == ARG_ERROR)
	{
		ft_putstr_fd("invalid argument: ", 2);
		ft_putendl_fd(str, 2);
		print_instruction();
	}
	else
		ft_putendl_fd(strerror(errnum), 2);
	if (data != NULL)
		data = data_free(data);
	exit(errnum);
}
