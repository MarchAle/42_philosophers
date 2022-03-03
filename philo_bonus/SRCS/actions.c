/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:14:16 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/02 13:55:56 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

int	ft_take_fork(t_philo *philo)
{
	while (1)
	{
		if (philo->p->forks > 0)
			break ;
		if (ft_am_i_dead(philo))
			return (0);
		usleep(philo->p->tempo);
	}
	sem_wait(philo->p->semaphore);
	philo->p->forks -= 1;
	printf("\033[%dm%ld %d has taken a fork\033[0m\n", philo->color,
		ft_get_time() - philo->start_time, philo->index);
	return (1);
}

// int	ft_take_second_fork(t_philo *philo)
// {
// 	while (1)
// 	{
// 		if (philo->p->philos[(philo->index) % philo->p->nb_phi].fork_lock == 0)
// 			break ;
// 		if (ft_am_i_dead(philo))
// 			return (0);
// 		usleep(philo->p->tempo);
// 	}
// 	philo->p->philos[(philo->index) % philo->p->nb_phi].fork_lock = 1;
// 	pthread_mutex_lock(&philo->p->philos[(philo->index)
// 		% philo->p->nb_phi].fork);
// 	printf("\033[%dm%ld %d has taken a fork\033[0m\n", philo->color,
// 		ft_get_time() - philo->start_time, philo->index);
// 	return (1);
// }

int	ft_think(t_philo *philo)
{
	printf("\033[%dm%ld %d is thinking\033[0m\n", philo->color,
		ft_get_time() - philo->start_time, philo->index);
	if (!ft_take_fork(philo))
		return (0);
	if (!ft_take_fork(philo))
		return (0);
	return (1);
}

int	ft_eat(t_philo *philo)
{
	printf("\033[%dm%ld %d is eating\033[0m\n", philo->color,
		ft_get_time() - philo->start_time, philo->index);
	philo->nb_meal++;
	if (philo->p->nb_of_eat)
		if (ft_check_meal(philo))
			return (0);
	philo->last_meal = ft_get_time();
	while (ft_get_time() < philo->p->t_eat + philo->last_meal)
	{
		if (ft_am_i_dead(philo))
			return (0);
		usleep(philo->p->tempo);
	}
	philo->p->forks += 2;
	sem_post(philo->p->semaphore);
	sem_post(philo->p->semaphore);
	// pthread_mutex_unlock(&philo->fork);
	// pthread_mutex_unlock(&philo->p->philos[(philo->index)
	// 	% philo->p->nb_phi].fork);
	// philo->fork_lock = 0;
	// philo->p->philos[(philo->index) % philo->p->nb_phi].fork_lock = 0;
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	printf("\033[%dm%ld %d is sleeping\033[0m\n", philo->color,
		ft_get_time() - philo->start_time, philo->index);
	while (ft_get_time() < philo->p->t_sleep
		+ philo->last_meal + philo->p->t_eat)
	{
		if (ft_am_i_dead(philo))
			return (0);
		usleep(philo->p->tempo);
	}
	usleep(100);
	return (1);
}
