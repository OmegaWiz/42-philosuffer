/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:23:03 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/06/20 10:33:38 by kkaiyawo         ###   ########.fr       */
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
# ifndef COLOR
#  define COLOR 1
# endif

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

typedef enum e_status
{
	THINK_I,
	THINK_U,
	EAT,
	SLEEP,
}	t_status;

typedef enum e_error
{
	ARG_ERROR,
	THREAD_ERROR,
	MALLOC_ERROR,
	MUTEX_ERROR,
	GETTIMEOFDAY_ERROR,
}	t_error;

typedef struct s_data
{
	int			philo_cnt;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eat_cnt;
	int			full_cnt;
	bool		is_dead;
	t_timeval	start;
	t_mutex		*forks;
	t_mutex		dead;
	t_mutex		print;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				eat_cnt;
	t_status		status;
	t_timeval		last_eat;
	t_timeval		last_sleep;
	t_timeval		now;
	int				lfork;
	int				rfork;
	pthread_t		thread;
	t_data			*data;
}					t_philo;

// philo.c
void		print_instruction(void);
void		philo_error(t_data *data, char *str, t_error error, int errnum);

// data_utils.c
void		data_init(t_data *data, int argc, char **argv);
t_data		*data_free(t_data *data);

// philo_utils.c
t_philo		*philo_init(t_data *data, int argc, char **argv);
t_philo		*philo_free(t_philo *philo);

// philo_cycle.c
void		*philo_cycle(void *arg);

// cycle_utils.c
int			get_timerel(void);
t_timeval	get_timeval(void);
bool		set_dead(t_data *data)
bool		is_dead(t_philo *philo);

// ft_atou.c
int			ft_atou_warn(const char *nptr);

#endif
