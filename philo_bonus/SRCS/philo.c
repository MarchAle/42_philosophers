/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:28:35 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/07 16:04:24 by amarchal         ###   ########.fr       */
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

int	ft_philo(int pid, int i, t_philo *philo)
{
	(void)pid;
	(void)i;
	// t_philo	*philo;

	// philo = &param->philos[i];
	// philo->pid = pid;
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
	sem_post(philo->p->sem_dead);
	// sem_close(semaphore);
	return (0);
}
