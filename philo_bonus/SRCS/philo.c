/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:28:35 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/02 14:02:27 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

int	ft_am_i_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->p->nb_phi)
	{
		if (philo->p->philos[i].dead == 1)
			return (1);
		i++;
	}
	if (ft_get_time() >= philo->last_meal + philo->p->t_die)
	{
		printf("%ld %d died\n", ft_get_time() - philo->start_time, philo->index);
		return (1);
	}
	return (0);
}

// void	ft_mutex_destroy(t_param *p)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < p->nb_phi)
// 	{
// 		pthread_mutex_unlock(&p->philos[i].fork);
// 		pthread_mutex_destroy(&p->philos[i].fork);
// 	}
// }

void	*ft_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->start_time = ft_get_time();
	philo->last_meal = ft_get_time();
	while (1)
	{
		if (!ft_think(philo))
			break ;
		if (!ft_eat(philo))
			break ;
		if (!ft_sleep(philo))
			break ;
	}
	philo->dead = 1;
	sem_close(philo->p->semaphore);
	return (0);
}
