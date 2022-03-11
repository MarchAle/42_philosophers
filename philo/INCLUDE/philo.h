/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:50:29 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/11 16:47:03 by amarchal         ###   ########.fr       */
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
	pthread_t		thread;
	pthread_mutex_t	fork;
	long			last_meal;
	pthread_mutex_t	last_meal_m;
	int				nb_meal;
	pthread_mutex_t	nb_meal_m;
	int				stop;
	pthread_mutex_t	stop_m;
	int				index;
	long			start_time;
	int				color;
	struct s_param	*p;
}	t_philo;

typedef struct s_param
{
	int				nb_phi;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				nb_of_eat;
	t_philo			*philos;
	pthread_mutex_t	msg_m;
	int				tempo;
}	t_param;

long int	ft_atoi(const char *str);
int			ft_check_args(char **av);
int			ft_dinner_end(t_param *param);
void		*ft_philo(void *param);
long		ft_get_time(void);
void		ft_mutex_destroy(t_param *param);
int			ft_take_first_fork(t_philo *philo);
int			ft_take_second_fork(t_philo *philo);
int			ft_think(t_philo *philo);
int			ft_eat(t_philo *philo);
int			ft_sleep(t_philo *philo);
int			ft_should_i_stop(t_philo *philo);
int			ft_check_death(t_param *param, int i);
int			ft_dinner_end(t_param *param);
int			ft_check_dinner(t_param *param, int i);
int			ft_monitoring(t_param *param);

#endif