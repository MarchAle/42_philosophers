/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:28:35 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/04 17:30:52 by amarchal         ###   ########.fr       */
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

int	ft_philo(int pid, int i, t_param *param)
{
	(void)pid;
	t_philo	*philo;

	philo = &param->philos[i];
	philo->index = i;
	philo->start_time = ft_get_time();
	philo->last_meal = ft_get_time();
	param->semafork = sem_open(SEM_NAME, O_RDWR, 0644, param->nb_phi);
	// philo->nb_meal = 0;
	// printf("Hello je suis philo %d avec le pid %d\n", i, pid);
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
	sem_close(philo->p->semafork);
	return (0);
}
