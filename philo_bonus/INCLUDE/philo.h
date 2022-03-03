/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:50:29 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/02 14:09:07 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "../INCLUDE/philo.h"

# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	int				index;
	long			start_time;
	pthread_t		thread;
	// pthread_mutex_t	fork;
	// int				fork_lock;
	long			last_meal;
	int				nb_meal;
	struct s_param	*p;
	int				dead;
	int				color;
}	t_philo;

typedef struct s_param
{
	sem_t		*semaphore;
	int			forks;
	int			nb_phi;
	long		t_die;
	long		t_eat;
	long		t_sleep;
	int			nb_of_eat;
	t_philo		*philos;
	int			tempo;
}	t_param;

long int	ft_atoi(const char *str);
int			ft_check_args(char **av);
int			ft_check_meal(t_philo *philo);
void		*ft_philo(void *param);
long		ft_get_time(void);
void		ft_putnbr_fd(int n, int fd);
// void		ft_mutex_destroy(t_param *param);
int			ft_am_i_dead(t_philo *philo);
int			ft_take_fork(t_philo *philo);
// int			ft_take_second_fork(t_philo *philo);
int			ft_think(t_philo *philo);
int			ft_eat(t_philo *philo);
int			ft_sleep(t_philo *philo);

#endif