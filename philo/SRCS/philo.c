/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:28:35 by amarchal          #+#    #+#             */
/*   Updated: 2022/02/23 17:28:40 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

void	ft_eat(t_philo *philo, int index)
{
	pthread_mutex_lock(&philo->fork);
	if (philo->index == philo->param->nb_of_philo - 1)
	{
		pthread_mutex_lock(&philo->param->philos[0].fork);
	}
	else
	{
		pthread_mutex_lock(&philo->param->philos[index + 1].fork);
	}
	printf("\033[94mPhilo %d start eating\033[0m\n", index);
	// while (philo->start_time + philo->param->time_to_eat < ft_get_time())
	// {
		usleep(200 * 1000);
	// }
	pthread_mutex_unlock(&philo->fork);
	if (philo->index == philo->param->nb_of_philo - 1)
		pthread_mutex_unlock(&philo->param->philos[0].fork);
	else
		pthread_mutex_unlock(&philo->param->philos[index + 1].fork);
}

void	ft_sleep(t_philo *philo)
{
	printf("\033[95mPhilo %d start sleeping\033[0m\n", philo->index);
	usleep(philo->param->time_to_sleep * 1000);
}

void	*ft_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->start_time = ft_get_time();
	// while (1)
	// {
		ft_eat(philo, philo->index);
		printf("time from start = %ld\n", ft_get_time() - philo->start_time);
		ft_sleep(philo);
		printf("time from start = %ld\n", ft_get_time() - philo->start_time);
	// }
	return (0);
}