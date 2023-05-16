/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:28:45 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/16 11:50:26 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	int				num_of_philo;
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

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_error("Error: Wrong number of arguments\n"));
	if (ft_init(argc, argv) == -1)
		return (-1);
	return (0);
}

int	ft_init(int argc, char **argv)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (ft_error("Error: malloc failed\n"));
	if (ft_parse(argc, argv, philo) == -1)
		return (-1);
	if (ft_init_mutex(philo) == -1)
		return (-1);
	if (ft_create_thread(philo) == -1)
		return (-1);
	return (0);
}

int	ft_parse(int argc, char **argv, t_philo *philo)
{
	philo->num_of_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->num_of_eat = ft_atoi(argv[5]);
	else
		philo->num_of_eat = -1;
	if (philo->num_of_philo < 2 || philo->num_of_philo > 200)
		return (ft_error("Error: Wrong number of philosophers\n"));
	if (philo->time_to_die < 60 || philo->time_to_eat < 60
		|| philo->time_to_sleep < 60)
		return (ft_error("Error: Wrong time\n"));
	if (argc == 6 && philo->num_of_eat < 1)
		return (ft_error("Error: Wrong number of eat\n"));
	return (0);
}

int	ft_init_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->num_of_philo);
	if (!philo->forks)
		return (ft_error("Error: malloc failed\n"));
	while (i < philo->num_of_philo)
	{
		if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
			return (ft_error("Error: mutex init failed\n"));
		i++;
	}
	if (pthread_mutex_init(&philo->print, NULL) != 0)
		return (ft_error("Error: mutex init failed\n"));
	return (0);
}

int	ft_create_thread(t_philo *philo)
{
	int			i;
	pthread_t	*thread;

	i = 0;
	thread = malloc(sizeof(pthread_t) * philo->num_of_philo);
	if (!thread)
		return (ft_error("Error: malloc failed\n"));
	philo->start_time = ft_get_time();
	while (i < philo->num_of_philo)
	{
		if (pthread_create(&thread[i], NULL, ft_philo, philo) != 0)
			return (ft_error("Error: thread creation failed\n"));
		pthread_detach(thread[i]);
		i++;
	}
	while (1)
	{
		if (ft_check_death(philo) == 1)
			break ;
		usleep(1000);
	}
	free(thread);
	return (0);
}

int	ft_check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		if (philo->philo[i].is_eating == 0
			&& ft_get_time() - philo->philo[i].last_eat > philo->time_to_die)
		{
			pthread_mutex_lock(&philo->print);
			printf("%ld %d died\n", ft_get_time() - philo->start_time,
				philo->philo[i].id);
			return (1);
		}
		i++;
	}
	if (philo->num_of_eat != -1)
	{
		if (philo->num_of_eat == 0)
		{
			pthread_mutex_lock(&philo->print);
			return (1);
		}
	}
	return (0);
}

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->philo[philo->id].last_eat = ft_get_time();
	philo->philo[philo->id].is_eating = 0;
	while (1)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->id]);
	pthread_mutex_lock(&philo->forks[(philo->id + 1)
			% philo->num_of_philo]);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "has taken a fork");
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->print);
	philo->philo[philo->id].is_eating = 1;
	philo->philo[philo->id].last_eat = ft_get_time();
	philo->num_of_eat--;
	ft_print(philo, "is eating");
	pthread_mutex_unlock(&philo->print);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->forks[philo->id]);
	pthread_mutex_unlock(&philo->forks[(philo->id + 1)
			% philo->num_of_philo]);
	philo->philo[philo->id].is_eating = 0;
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	ft_print(philo, "is thinking");
}

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->print);
	printf("%ld %d %s\n", ft_get_time() - philo->start_time,
		philo->philo[philo->id].id, str);
	pthread_mutex_unlock(&philo->print);
}

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_error(char *str)
{
	printf("%s", str);
	return (1);
}

void	ft_free(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->print);
	free(philo->forks);
	free(philo->philo);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!str)
		return (-1);
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -sign;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (-1);
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

