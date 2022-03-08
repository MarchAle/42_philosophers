/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:14:16 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/08 17:17:10 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

int	ft_take_fork(t_philo *philo)
{
	sem_wait(philo->p->semaphore);
	printf("\033[%dm%ld %d has taken a fork\033[0m\n", philo->color,
		ft_get_time() - philo->start_time, philo->index);
	return (1);
}

int	ft_think(t_philo *philo)
{
	printf("\033[%dm%ld %d is thinking\033[0m\n", philo->color,
		ft_get_time() - philo->start_time, philo->index);
	// if (!ft_take_fork(philo))
	// 	return (0);
	// if (!ft_take_fork(philo))
	// 	return (0);
	ft_take_fork(philo);
	ft_take_fork(philo);
	return (1);
}

int	ft_eat(t_philo *philo)
{
	printf("\033[%dm%ld %d is eating\033[0m\n", philo->color,
		ft_get_time() - philo->start_time, philo->index);
	philo->nb_meal++;
	if (philo->p->nb_of_eat)
		ft_check_meal(philo);
	philo->last_meal = ft_get_time();
	// ft_usleep(philo->p->t_eat);
	while (ft_get_time() < philo->p->t_eat + philo->last_meal)
	{
		// if (ft_am_i_dead(philo))
		// 	return (0);
		usleep(philo->p->tempo);
	}
	// usleep(200 * 1000);
	sem_post(philo->p->semaphore);
	sem_post(philo->p->semaphore);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	int	i;

	i = 0;
	printf("\033[%dm%ld %d is sleeping\033[0m\n", philo->color,	ft_get_time() - philo->start_time, philo->index);
	while (ft_get_time() < philo->p->t_sleep + philo->last_meal + philo->p->t_eat)
	{
		// if (ft_am_i_dead(philo))
		// 	return (0);
		usleep(philo->p->tempo);
	}
	// usleep(200 * 1000);
	return (1);
}
