/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:14:16 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/04 11:43:59 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

int	ft_take_first_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->fork);
		if (philo->fork_lock == 0)
		{
			pthread_mutex_unlock(&philo->fork);
			break ;
		}
		pthread_mutex_unlock(&philo->fork);
		if (ft_am_i_dead(philo))
			return (0);
		usleep(philo->p->tempo);
	}
	pthread_mutex_lock(&philo->fork);
	philo->fork_lock = 1;
	pthread_mutex_unlock(&philo->fork);
	printf("\033[%dm%ld %d has taken a fork\033[0m\n", philo->color,
		ft_get_time() - philo->start_time, philo->index);
	return (1);
}

int	ft_take_second_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->p->philos[(philo->index)
			% philo->p->nb_phi].fork);
		if (philo->p->philos[(philo->index) % philo->p->nb_phi].fork_lock == 0)
		{
			pthread_mutex_unlock(&philo->p->philos[(philo->index)
				% philo->p->nb_phi].fork);
			break ;
		}
		pthread_mutex_unlock(&philo->p->philos[(philo->index)
			% philo->p->nb_phi].fork);
		if (ft_am_i_dead(philo))
			return (0);
		usleep(philo->p->tempo);
	}
	pthread_mutex_lock(&philo->p->philos[(philo->index)
		% philo->p->nb_phi].fork);
	philo->p->philos[(philo->index) % philo->p->nb_phi].fork_lock = 1;
	pthread_mutex_unlock(&philo->p->philos[(philo->index)
		% philo->p->nb_phi].fork);
	printf("\033[%dm%ld %d has taken a fork\033[0m\n", philo->color,
		ft_get_time() - philo->start_time, philo->index);
	return (1);
}

int	ft_think(t_philo *philo)
{
	printf("\033[%dm%ld %d is thinking\033[0m\n", philo->color,
		ft_get_time() - philo->start_time, philo->index);
	if (!ft_take_first_fork(philo))
		return (0);
	if (!ft_take_second_fork(philo))
		return (0);
	return (1);
}

int	ft_eat(t_philo *philo)
{
	printf("\033[%dm%ld %d is eating\033[0m\n", philo->color,
		ft_get_time() - philo->start_time, philo->index);
	pthread_mutex_lock(&philo->mil);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->mil);
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
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->p->philos[(philo->index)
		% philo->p->nb_phi].fork);
	philo->fork_lock = 0;
	philo->p->philos[(philo->index) % philo->p->nb_phi].fork_lock = 0;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->p->philos[(philo->index)
		% philo->p->nb_phi].fork);
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
