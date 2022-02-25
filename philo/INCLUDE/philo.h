/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:50:29 by amarchal          #+#    #+#             */
/*   Updated: 2022/02/25 14:36:15 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include "../INCLUDE/philo.h"

# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	int				index;
	pthread_t		thread;
	pthread_mutex_t	fork;
	int				fork_lock;
	struct s_param	*param;
	long			start_time;
	long			last_meal;
	int				nb_meal;
	int				dead;
	int				color;
}	t_philo;

typedef struct s_param
{
	int			nb_of_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			nb_of_eat;
	t_philo		*philos;
}	t_param;

long int	ft_atoi(const char *str);
int			ft_check_args(char **av);
void		*ft_philo(void *param);
long		ft_get_time(void);

#endif