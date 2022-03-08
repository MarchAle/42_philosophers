/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:50:29 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/08 17:23:41 by amarchal         ###   ########.fr       */
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
# include <signal.h>
# include "../INCLUDE/philo.h"

# define TRUE 1
# define FALSE 0
# define SEM_FORK "/sem"
# define SEM_DEAD "/sem_dead"
# define SEM_MEAL "/sem_meal"

typedef struct s_philo
{
	pthread_t		monitor;
	int				pid;
	int				index;
	long			start_time;
	long			last_meal;
	int				nb_meal;
	struct s_param	*p;
	int				color;
	long			t_die;
}	t_philo;

typedef struct s_param
{
	pthread_t	meal_monitor;
	sem_t		*semaphore;
	sem_t		*sem_dead;
	sem_t		*sem_meal;
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
void		ft_check_meal(t_philo *philo);
int			ft_philo(t_philo *philo);
long		ft_get_time(void);
void		ft_putnbr_fd(int n, int fd);
int			ft_am_i_dead(t_philo *philo);
int			ft_take_fork(t_philo *philo);
int			ft_think(t_philo *philo);
int			ft_eat(t_philo *philo);
int			ft_sleep(t_philo *philo);
void		ft_usleep(int ms);

#endif