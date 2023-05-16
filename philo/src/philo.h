/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:23:03 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/16 10:21:32 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <string.h>
// memset
# include <stdio.h>
// printf
# include <stdlib.h>
// malloc free
# include <unistd.h>
// write usleep
# include <sys/time.h>
// gettimeofday
# include <pthread.h>
// pthread_create pthread_detach pthread_join pthread_mutex_init
// pthread_mutex_destroy pthread_mutex_lock pthread_mutex_unlock

# ifndef STDIN_FILENO
#  define STDIN_FILENO 0
# endif
# ifndef STDOUT_FILENO
#  define STDOUT_FILENO 1
# endif
# ifndef STDERR_FILENO
#  define STDERR_FILENO 2
# endif
# ifndef BONUS
#  define BONUS 0
# endif

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				is_eating;
	int				is_sleeping;
	int				is_thinking;
	int				is_dead;
	int				left_fork;
	int				right_fork;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	long			start_time;
	long			last_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*eat;
}					t_philo;

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	int				is_dead;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*eat;
}					t_data;

#endif
