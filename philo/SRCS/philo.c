/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:28:35 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/11 11:48:08 by amarchal         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->last_meal_m);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->last_meal_m);
	while (1)
	{
		if (!ft_think(philo))
			break ;
		if (ft_should_i_stop(philo) == TRUE)
			return (0);
		if (!ft_eat(philo))
			break ;
		if (ft_should_i_stop(philo) == TRUE)
			return (0);
		if (!ft_sleep(philo))
			break ;
		if (ft_should_i_stop(philo) == TRUE)
			return (0);
	}
	return (0);
}
