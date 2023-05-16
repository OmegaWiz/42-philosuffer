/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:23:03 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/16 15:18:47 by kkaiyawo         ###   ########.fr       */
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
# include <stdbool.h>
// bool true false
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

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

typedef struct s_data
{
	int			philo_cnt;
	long		die_time;
	long		eat_time;
	long		bed_time;
	int			min_eat;
	bool		end;
	t_timeval	start;
	t_mutex	*fork;
}					t_data;

typedef struct s_philo
{
	int			id;
	t_data		*data;
	pthread_t	thread;
	t_timeval	last_eat;
	int			eat_cnt;
}					t_philo;

enum e_error
{
	ARGC_ERROR,
	THREAD_ERROR,
	MALLOC_ERROR,
};

enum e_state
{
	FORK,
	EAT,
	SLEEP,
	THINK,
};

void	philo_init(t_philo **philo, t_data *data, int argc, char **argv);
void	*philo_cycle(void *ptr);
bool	is_dead(t_philo *philo, t_timeval now);
void	philo_print(t_philo *philo, enum e_state state, t_timeval now);
void	philo_take_fork(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_free(t_philo **philo, t_data *data);
void	philo_error(t_philo **philo, char *msg, enum e_error err, int errnum);

void	*malloc_check(size_t size);

#endif
