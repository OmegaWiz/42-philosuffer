/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:51:48 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/20 15:38:41 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isblank(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	if (c == '\n')
		return (1);
	return (0);
}

int	atou_err(char *num, char *errmsg, int is_err)
{
	ft_putstr_fd(BBLU"philo: "RESET, 2);
	ft_putstr_fd(num, 2);
	ft_putstr_fd(": ", 2);
	if (is_err == 0)
		ft_putstr_fd(BYEL"Warning: ", 2);
	else
		ft_putstr_fd(BRED": Error: ", 2);
	ft_putstr_fd(errmsg, 2);
	ft_putstr_fd("\n"RESET, 2);
	return (-1);
}

long long	ft_atou_warn(char *nptr)
{
	size_t		neg;
	long long	num;
	size_t		i;

	neg = 0;
	num = 0;
	i = 0;
	while (ft_isblank(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		return (-1);
	while ('0' <= nptr[i] && nptr[i] <= '9' && num <= 99999999999)
		num = (num * 10) + (nptr[i++] - '0');
	if (neg % 2)
		return (atou_err(nptr, "Number is negative\n", 0));
	if (num > INT_MAX)
		return (atou_err(nptr, "Number is too large\n", 1));
	if (nptr[i] != '\0')
		atou_err(nptr, "Parts of string is not considered as a number", 0);
	return (num);
}
