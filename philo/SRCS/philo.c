/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:28:35 by amarchal          #+#    #+#             */
/*   Updated: 2022/02/22 18:25:14 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

void	ft_eat(t_philo *philo, int index)
{
	t_philo	*neighbour;

	printf("Index : %d\n", index);
	pthread_mutex_lock(&philo->mutex);
	if (index == philo->param->nb_of_philo - 1)
		index = 0;
	else
		index += 1;
	neighbour = &philo->param->philos[index];
	pthread_mutex_lock(&neighbour->mutex);
	printf("My fork is : %d\n", philo->fork);
	printf("My neighbour fork is : %d\n", neighbour->fork);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&neighbour->mutex);
}

void	*ft_philo(void *data)
{
	printf("\033[94mHello je suis philo %d\033[0m\n", ((t_philo *)data)->index);
	ft_eat((t_philo *)data, ((t_philo *)data)->index);
	return (0);
}