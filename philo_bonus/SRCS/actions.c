/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:14:16 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/14 11:18:45 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

void	ft_take_fork(t_philo *philo)
{
	sem_wait(philo->p->semafork);
	sem_wait(philo->p->sem_msg);
	printf("\033[%dm%ld %d has taken a fork\033[0m\n", philo->color,
		ft_get_time() - philo->p->start_time, philo->index);
	sem_post(philo->p->sem_msg);
}

void	ft_think(t_philo *philo)
{
	sem_wait(philo->p->sem_msg);
	printf("\033[%dm%ld %d is thinking\033[0m\n", philo->color,
		ft_get_time() - philo->p->start_time, philo->index);
	sem_post(philo->p->sem_msg);
	ft_take_fork(philo);
	ft_take_fork(philo);
}

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->p->sem_msg);
	printf("\033[%dm%ld %d is eating\033[0m\n", philo->color,
		ft_get_time() - philo->p->start_time, philo->index);
	sem_post(philo->p->sem_msg);
	philo->nb_meal++;
	if (philo->p->nb_of_eat)
		ft_check_meal(philo);
	philo->last_meal = ft_get_time();
	while (ft_get_time() < philo->p->t_eat + philo->last_meal)
		usleep(philo->p->tempo);
	sem_post(philo->p->semafork);
	sem_post(philo->p->semafork);
}

void	ft_sleep(t_philo *philo)
{
	sem_wait(philo->p->sem_msg);
	printf("\033[%dm%ld %d is sleeping\033[0m\n",
		philo->color, ft_get_time() - philo->p->start_time, philo->index);
	sem_post(philo->p->sem_msg);
	while (ft_get_time() < philo->p->t_sleep
		+ philo->last_meal + philo->p->t_eat)
		usleep(philo->p->tempo);
}
