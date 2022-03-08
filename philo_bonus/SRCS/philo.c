/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:28:35 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/08 17:09:02 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

int	ft_am_i_dead(t_philo *philo)
{
	if (ft_get_time() >= philo->last_meal + philo->p->t_die)
	{
		printf("%ld %d died\n", ft_get_time() - philo->start_time, philo->index);
		return (1);
	}
	return (0);
}

void	*ft_monitor(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		if (ft_get_time() >= philo->last_meal + philo->p->t_die)
		{
			printf("%ld %d died\n", ft_get_time() - philo->start_time, philo->index);
			sem_post(philo->p->sem_dead);
		}
		usleep(100);
	}
}

int	ft_philo(t_philo *philo)
{
	philo->start_time = ft_get_time();
	philo->last_meal = ft_get_time();
	if (pthread_create(&philo->monitor, NULL, ft_monitor, philo) != 0)
		return (0);
	while (1)
	{
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
		// if (!ft_think(philo))
		// 	break ;
		// if (!ft_eat(philo))
		// 	break ;
		// if (!ft_sleep(philo))
		// 	break ;
	}
	// sem_post(philo->p->sem_dead);
	return (0);
}
