/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:14:16 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/10 17:25:13 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

int	ft_take_first_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	if (ft_should_i_stop(philo))
			return (0);
	printf("\033[%dm%ld %d has taken a fork\033[0m\n", philo->color,
		ft_get_time() - philo->start_time, philo->index);
	return (1);
}

int	ft_take_second_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->p->philos[(philo->index)
		% philo->p->nb_phi].fork);
	if (ft_should_i_stop(philo))
			return (0);
	printf("\033[%dm%ld %d has taken a fork\033[0m\n", philo->color,
		ft_get_time() - philo->start_time, philo->index);
	return (1);
}

int	ft_think(t_philo *philo)
{
	printf("\033[%dm%ld %d is thinking\033[0m\n", philo->color,
		ft_get_time() - philo->start_time, philo->index);
	if (philo->nb_meal == 0 && philo->index % 2 == 0)
		usleep(10000);
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
	pthread_mutex_lock(&philo->meal);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->meal);
	// pthread_mutex_lock(&philo->last_meal_m);
	philo->last_meal = ft_get_time();
	// pthread_mutex_unlock(&philo->last_meal_m);
	while (ft_get_time() < philo->p->t_eat + philo->last_meal)
	{
		usleep(philo->p->tempo);
	}
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
		usleep(philo->p->tempo);
	}
	return (1);
}
