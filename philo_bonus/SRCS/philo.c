/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:28:35 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/11 14:46:17 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

void	*ft_monitor(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		if (ft_get_time() >= philo->last_meal + philo->p->t_die)
		{
			sem_wait(philo->p->sem_msg);
			usleep(100);
			printf("%ld %d died\n", ft_get_time() - philo->p->start_time,
				philo->index);
			sem_post(philo->p->sem_end);
		}
		usleep(philo->p->tempo);
	}
}

int	ft_philo(t_philo *philo)
{
	philo->last_meal = ft_get_time();
	philo->p->start_time = ft_get_time();
	if (pthread_create(&philo->death_monitor, NULL, ft_monitor, philo) != 0)
		exit(EXIT_FAILURE);
	while (1)
	{
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
	return (0);
}
