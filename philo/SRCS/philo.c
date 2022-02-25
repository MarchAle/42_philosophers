/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:28:35 by amarchal          #+#    #+#             */
/*   Updated: 2022/02/25 17:50:59 by amarchal         ###   ########.fr       */
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
		printf("%ld ms Philo %d died\nLast_meal : %ld\nRIP\n", ft_get_time() - philo->start_time, philo->index, philo->last_meal);
		return (1);
	}
	return (0);
}

int	ft_think(t_philo *philo)
{
	long	i = 0;
	i = ft_get_time();
	// printf("Mon index : %d | Index voisin : %d\n", philo->index - 1, philo->param->philos[(philo->index) % (philo->param->nb_of_philo)].index - 1);
	while (1)
	{
		// printf("My fork = %d | Neighbour's fork = %d\n", philo->fork_lock, philo->param->philos[(philo->index + 1) % philo->param->nb_of_philo].fork_lock);
		if (philo->fork_lock == 0 && philo->param->philos[(philo->index) % philo->param->nb_of_philo].fork_lock == 0)
			break;
		if (ft_am_i_dead(philo))
			return (0);
		// usleep(1 * 1000);
		// philo->last_meal++;
		// philo->start_time++;
		// i++;
	}
	i = ft_get_time() - i;
	printf("\033[%dmJ'ai pensé %ld ms\033[0m\n", philo->color, i);
	// printf("Ma fork : %d | Fork voisin : %d\n", philo->fork_lock, philo->param->philos[(philo->index) % philo->param->nb_of_philo].fork_lock);
	printf("\033[%dm%ld ms Philo %d has taken a fork\033[0m\n", philo->color, ft_get_time() - philo->start_time, philo->index);
	printf("\033[%dm%ld ms Philo %d is eating\033[0m\n", philo->color, ft_get_time() - philo->start_time, philo->index);
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

int	ft_eat(t_philo *philo)
{
	long	i;
	philo->fork_lock = 1;
	philo->param->philos[(philo->index) % philo->param->nb_of_philo].fork_lock = 1;
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->param->philos[(philo->index) % philo->param->nb_of_philo].fork);
	philo->last_meal = 0;
	philo->nb_meal++;
	if (philo->param->nb_of_eat)
		if (ft_check_meal(philo))
			return (0);
	i = ft_get_time();
	// while (philo->last_meal < philo->param->time_to_eat)
	while (ft_get_time() - i < philo->param->time_to_eat)
	{
		// printf("HOUHOU\n");
		if (ft_am_i_dead(philo))
			return (0);
		// usleep(1 * 1000);
		// philo->last_meal++;
		// philo->start_time++;
	}
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->param->philos[(philo->index) % philo->param->nb_of_philo].fork);
	philo->fork_lock = 0;
	philo->param->philos[(philo->index) % philo->param->nb_of_philo].fork_lock = 0;
	i = ft_get_time() - i;
	printf("\033[%dmJ'ai mangé %ld ms\033[0m\n", philo->color, i);
	printf("\033[%dm%ld ms Philo %d is sleeping\033[0m\n", philo->color, ft_get_time() - philo->start_time, philo->index);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	long i;

	i = ft_get_time();
	// while (++i < philo->param->time_to_sleep)
	while (ft_get_time() - i < philo->param->time_to_sleep)
	{
		if (ft_am_i_dead(philo))
			return (0);
		// usleep(1 * 1000);
		// philo->last_meal++;
		// philo->start_time++;
		// i++;
	}
	i = ft_get_time() - i;
	printf("\033[%dmJ'ai dormi %ld ms\033[0m\n", philo->color, i);
	printf("\033[%dm%ld ms Philo %d is thinking\033[0m\n", philo->color, ft_get_time() - philo->start_time, philo->index);
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
	if (philo->index % 2 == 0)
		usleep(1 * 1000);
	philo->start_time = ft_get_time();
	while (1)
	{
		if (!ft_think(philo))
			break;
		if (!ft_eat(philo))
			break;
		if (!ft_sleep(philo))
			break;
	}
	philo->dead = 1;
	ft_mutex_destroy(philo);
	return (0);
}
