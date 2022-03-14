/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:26:19 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/14 11:09:50 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

void	ft_init_sem(t_param *param)
{
	sem_t	*semafork;
	sem_t	*sem_end;
	sem_t	*sem_meal;
	sem_t	*sem_msg;

	sem_unlink(SEM_FORK);
	sem_unlink(SEM_END);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_MSG);
	semafork = sem_open(SEM_FORK, O_CREAT | O_EXCL, 644, param->nb_phi);
	sem_end = sem_open(SEM_END, O_CREAT | O_EXCL, 644, 0);
	sem_meal = sem_open(SEM_MEAL, O_CREAT | O_EXCL, 644, 0);
	sem_msg = sem_open(SEM_MSG, O_CREAT | O_EXCL, 644, 1);
	if (semafork < 0 || sem_end < 0 || sem_meal < 0 || sem_msg < 0)
		exit(EXIT_FAILURE);
	param->semafork = semafork;
	param->sem_end = sem_end;
	param->sem_meal = sem_meal;
	param->sem_msg = sem_msg;
}

void	ft_get_param(t_param *param, char **av)
{
	param->nb_phi = ft_atoi(av[1]);
	if (param->nb_phi < 50)
		param->tempo = 100;
	else if (param->nb_phi < 120)
		param->tempo = 500;
	else
		param->tempo = 1000;
	param->t_die = ft_atoi(av[2]);
	param->t_eat = ft_atoi(av[3]);
	param->t_sleep = ft_atoi(av[4]);
	if (av[5])
		param->nb_of_eat = ft_atoi(av[5]);
	else
		param->nb_of_eat = 0;
	param->start_time = ft_get_time();
}

void	ft_init_table(t_param *param)
{
	int		i;
	t_philo	philo;

	i = 0;
	param->philos = malloc(sizeof(t_philo) * param->nb_phi);
	if (!param->philos)
		exit(EXIT_FAILURE);
	while (i < param->nb_phi)
	{
		philo.index = i + 1;
		philo.p = param;
		philo.last_meal = 0;
		philo.nb_meal = 0;
		philo.color = (i + 1) % 8 + 90;
		param->philos[i] = philo;
		i++;
	}
}
