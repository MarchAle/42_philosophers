/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:28:35 by amarchal          #+#    #+#             */
/*   Updated: 2022/02/24 18:19:53 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

int	ft_am_i_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->param->nb_of_philo)
	{
		if (philo->param->philos[i].dead == 1)
			return (1);
		i++;
	}
	if (philo->last_meal >= philo->param->time_to_die)
	{
		printf("%ld ms Philo %d died\nRIP\n", philo->start_time, philo->index);
		return (1);
	}
	return (0);
}

int	ft_think(t_philo *philo, int index)
{
	printf("\033[%dm%ld ms Philo %d is thinking\033[0m\n", philo->color, philo->start_time, index);
	while (philo->fork_lock || philo->param->philos[(index + 1) % philo->param->nb_of_philo].fork_lock)
	{
		if (ft_am_i_dead(philo))
			return (0);
		usleep(1 * 1000);
		philo->last_meal++;
		philo->start_time++;
	}
	return (1);
}

int ft_check_meal(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->param->nb_of_philo)
	{
		if (philo->param->philos[i].nb_meal < philo->param->nb_of_eat)
			return (0);
		i++;
	}
	return (1);
}

int	ft_eat(t_philo *philo, int index)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->param->philos[(index + 1) % philo->param->nb_of_philo].fork);
	philo->fork_lock = 1;
	philo->param->philos[(index + 1) % philo->param->nb_of_philo].fork_lock = 1;
	printf("\033[%dm%ld ms Philo %d has taken a fork\033[0m\n", philo->color, philo->start_time, index);
	printf("\033[%dm%ld ms Philo %d is eating\033[0m\n", philo->color, philo->start_time, index);
	philo->last_meal = 0;
	philo->nb_meal++;
	if (philo->param->nb_of_eat)
		if (ft_check_meal(philo))
			return (0);
	while (philo->last_meal < philo->param->time_to_eat)
	{
		if (ft_am_i_dead(philo))
			return (0);
		usleep(1 * 1000);
		philo->last_meal++;
		philo->start_time++;
	}
	philo->fork_lock = 0;
	philo->param->philos[(index + 1) % philo->param->nb_of_philo].fork_lock = 0;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->param->philos[(index + 1) % philo->param->nb_of_philo].fork);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	int i;

	i = -1;
	printf("\033[%dm%ld ms Philo %d is sleeping\033[0m\n", philo->color, philo->start_time, philo->index);
	while (++i < philo->param->time_to_sleep)
	{
		if (ft_am_i_dead(philo))
			return (0);
		usleep(1 * 1000);
		philo->last_meal++;
		philo->start_time++;
		// i++;
	}
	return (1);
}

void	ft_mutex_destroy(t_philo *philo)
{
	int	i;

	i = 0;
	while (i++ < philo->param->nb_of_philo)
	{
		pthread_mutex_unlock(&philo->param->philos[i].fork);
		pthread_mutex_destroy(&philo->param->philos[i].fork);
	}
}

void	*ft_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->index %2 == 0)
		usleep(1 * 1000);
	philo->start_time = 0;
	while (1)
	{
		if (!ft_think(philo, philo->index))
			break;
		if (!ft_eat(philo, philo->index))
			break;
		if (!ft_sleep(philo))
			break;
	}
	philo->dead = 1;
	ft_mutex_destroy(philo);
	return (0);
}
