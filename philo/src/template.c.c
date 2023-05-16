/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:35:09 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/16 14:27:30 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define PHILO_NUM 5

pthread_mutex_t	mutex;

void	*routine(void *num)
{
	struct timeval	tv;
	long			*sec;

	printf("Hello, I'm a philosopher %d\n", *(int *) num);
	pthread_mutex_lock(&mutex);
	sec = (long *) malloc(sizeof(long));
	printf("Philosopher #%d starts thinking\n", *(int *) num);
	usleep(2000000);
	printf("Philosopher #%d finishes thinking\n", *(int *) num);
	gettimeofday(&tv, NULL);
	*sec = tv.tv_sec;
	pthread_mutex_unlock(&mutex);
	return ((void *) sec);
}

int	main(int argc, char **argv)
{
	pthread_t	t[PHILO_NUM];
	int			i;
	long		*sec[PHILO_NUM];
	int			id[PHILO_NUM];

	(void) argc;
	(void) argv;
	pthread_mutex_init(&mutex, NULL);
	i = -1;
	while (++i < PHILO_NUM)
		id[i] = i + 1;
	i = -1;
	while (++i < PHILO_NUM)
	{
		if (pthread_create(t + i, NULL, &routine, id + i) != 0)
			return (1);
	}
	i = -1;
	while (++i < PHILO_NUM)
	{
		if (pthread_join(t[i], (void **) &sec[i]) != 0)
			return (1);
		printf("Philosopher #%d finished eating at %ld\n", i + 1, *(sec[i]));
		free(sec[i]);
	}
	i = -1;
	/*
	while (++i < PHILO_NUM)
		free(sec[i]);
		*/
	pthread_mutex_destroy(&mutex);
	return (0);
}
