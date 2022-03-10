/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:50:29 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/10 17:21:04 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include "../INCLUDE/philo.h"

# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	int				index;
	long			start_time;
	pthread_t		thread;
	pthread_mutex_t	fork;
	long			last_meal;
	pthread_mutex_t	last_meal_m;
	pthread_mutex_t	meal;
	int				nb_meal;
	struct s_param	*p;
	pthread_mutex_t	stop_m;
	int				stop;
	int				color;
}	t_philo;

typedef struct s_param
{
	// pthread_mutex_t	msg;
	int				nb_phi;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	// long			start_time;
	int				nb_of_eat;
	t_philo			*philos;
	int				tempo;
}	t_param;

long int	ft_atoi(const char *str);
int			ft_check_args(char **av);
int			ft_dinner_end(t_param *param);
void		*ft_philo(void *param);
long		ft_get_time(void);
// void		ft_putnbr_fd(int n, int fd);
void		ft_mutex_destroy(t_param *param);
// int			ft_am_i_dead(t_philo *philo);
int			ft_take_first_fork(t_philo *philo);
int			ft_take_second_fork(t_philo *philo);
int			ft_think(t_philo *philo);
int			ft_eat(t_philo *philo);
int			ft_sleep(t_philo *philo);
int			ft_should_i_stop(t_philo *philo);

#endif