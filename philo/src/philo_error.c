/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 08:45:12 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/20 15:43:00 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_instruction(void)
{
	ft_putstr_fd(BGRN"\n\nUsage: ./philo {number_of_philosophers}", 2);
	ft_putstr_fd(" {time_to_die} {time_to_eat} {time_to_sleep} ", 2);
	ft_putendl_fd("[number_of_times_each_philosopher_must_eat]"RESET, 2);
	ft_putstr_fd("{number_of_philosophers} (int: 1-200) - The", 2);
	ft_putendl_fd("number of philosophers and also the number of forks.", 2);
	ft_putstr_fd("{time_to_die} (int: >= 60) - If a philosopher didn't ", 2);
	ft_putstr_fd("start eating {time_to_die} milliseconds since the ", 2);
	ft_putstr_fd("beginning of their last meal or the beginning of the ", 2);
	ft_putstr_fd("simulation, they die.\n{time_to_eat} (int: >= 60) - ", 2);
	ft_putstr_fd("The time in milliseconds it takes for a philosopher to ", 2);
	ft_putendl_fd("eat. During that time, they'll need to hold two forks.", 2);
	ft_putstr_fd("{time_to_sleep} (int: >= 60) - The time in milli", 2);
	ft_putendl_fd("seconds the philosopher will spend sleeping.", 2);
	ft_putstr_fd("[number_of_times_each_philosopher_must_eat] ", 2);
	ft_putstr_fd("(int >= 1) - If all philosophers have eaten at least ", 2);
	ft_putstr_fd("[number_of_times_each_philosopher_must_eat] times,", 2);
	ft_putstr_fd("the simulation stops. If not specified, the simulation", 2);
	ft_putendl_fd(" stops when a philosopher dies\n", 2);
}

void	philo_error(t_philo *philo, char *str, t_error error, int errnum)
{
	ft_putstr_fd("philo: ", 2);
	if (error == ARG_ERROR)
	{
		ft_putstr_fd("invalid argument: ", 2);
		ft_putendl_fd(str, 2);
		print_instruction();
	}
	else
		ft_putendl_fd(strerror(errnum), 2);
	if (philo != NULL)
	{
		(*philo).data = data_free((*philo).data);
		philo = philo_free(philo);
	}
	exit(errnum);
}

void	data_error(t_data *data, char *str, t_error error, int errnum)
{
	ft_putstr_fd(BBLU"philo: "RESET, 2);
	if (error == ARG_ERROR)
	{
		ft_putstr_fd(BRED"invalid argument: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n"RESET, 2);
		print_instruction();
	}
	else
		ft_putendl_fd(strerror(errnum), 2);
	if (data != NULL)
		data = data_free(data);
	exit(errnum);
}
