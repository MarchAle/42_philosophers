/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:50:29 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/14 10:44:51 by amarchal         ###   ########.fr       */
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
# include <limits.h>
# include "../INCLUDE/philo.h"

# define TRUE 1
# define FALSE 0
# define SEM_FORK "/sem"
# define SEM_END "/sem_end"
# define SEM_MEAL "/sem_meal"
# define SEM_MSG "/sem_msg"

typedef struct s_philo
{
	pthread_t		death_monitor;
	pid_t			pid;
	int				index;
	long			last_meal;
	int				nb_meal;
	struct s_param	*p;
	int				color;
}	t_philo;

typedef struct s_param
{
	pthread_t	meal_monitor;
	sem_t		*semafork;
	sem_t		*sem_end;
	sem_t		*sem_meal;
	sem_t		*sem_msg;
	int			nb_phi;
	long		t_die;
	long		t_eat;
	long		t_sleep;
	long		start_time;
	int			nb_of_eat;
	t_philo		*philos;
	int			tempo;
}	t_param;

long int	ft_atoi(const char *str);
int			ft_check_args(char **av);
void		ft_check_meal(t_philo *philo);
int			ft_philo(t_philo *philo);
long		ft_get_time(void);
void		ft_take_fork(t_philo *philo);
void		ft_think(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_init_sem(t_param *param);
void		ft_get_param(t_param *param, char **av);
void		ft_init_table(t_param *param);

#endif