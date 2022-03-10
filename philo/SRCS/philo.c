/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:28:35 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/10 17:25:06 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

int	ft_should_i_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->stop_m);
	if (philo->stop == 1)
	{
		pthread_mutex_unlock(&philo->stop_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->stop_m);
	return (0);
}

// int	ft_am_i_dead(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo->p->nb_phi)
// 	{
// 		pthread_mutex_lock(&philo->p->philos[i].ded);
// 		if (philo->p->philos[i].dead == 1)
// 		{
// 			pthread_mutex_unlock(&philo->p->philos[i].ded);
// 			return (1);
// 		}
// 		pthread_mutex_unlock(&philo->p->philos[i].ded);
// 		i++;
// 	}
// 	if (ft_get_time() >= philo->last_meal + philo->p->t_die)
// 	{
// 		printf("%ld %d died\n", ft_get_time() - philo->start_time, philo->index);
// 		return (1);
// 	}
// 	return (0);
// }

void	ft_mutex_destroy(t_param *p)
{
	int	i;

	i = -1;
	while (++i < p->nb_phi)
	{
		pthread_mutex_unlock(&p->philos[i].fork);
		pthread_mutex_destroy(&p->philos[i].fork);
	}
}

void	*ft_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->start_time = ft_get_time();
	// pthread_mutex_lock(&philo->last_meal_m);
	philo->last_meal = ft_get_time();
	// pthread_mutex_unlock(&philo->last_meal_m);
	// if (philo->index % 2 == 0)
	// 	usleep(10000);
	while (1)
	{
		if (!ft_think(philo))
			break ;
		if (ft_should_i_stop(philo))
			return (0);
		if (!ft_eat(philo))
			break ;
		if (ft_should_i_stop(philo))
			return (0);
		if (!ft_sleep(philo))
			break ;
		if (ft_should_i_stop(philo))
			return (0);
	}
	// pthread_mutex_lock(&philo->ded);
	// philo->dead = 1;
	// pthread_mutex_unlock(&philo->ded);
	return (0);
}
