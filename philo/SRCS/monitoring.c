/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 11:35:15 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/11 18:03:19 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

int	ft_check_death(t_param *param, int i)
{
	int	j;

	j = 0;
	pthread_mutex_lock(&param->philos[i].last_meal_m);
	if (ft_get_time() >= param->philos[i].last_meal + param->t_die)
	{
		while (j < param->nb_phi)
		{
			pthread_mutex_lock(&param->philos[j].stop_m);
			param->philos[j].stop = 1;
			pthread_mutex_unlock(&param->philos[j].stop_m);
			pthread_mutex_unlock(&param->philos[j].fork);
			pthread_mutex_unlock(&param->philos[j].last_meal_m);
			j++;
		}
		pthread_mutex_lock(&param->msg_m);
		usleep(100);
		printf("%ld %d died\n", ft_get_time() - param->philos[i].start_time,
			param->philos[i].index);
		pthread_mutex_unlock(&param->msg_m);
		return (0);
	}
	pthread_mutex_unlock(&param->philos[i].last_meal_m);
	return (1);
}

int	ft_dinner_end(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->nb_phi)
	{
		pthread_mutex_lock(&param->philos[i].nb_meal_m);
		if (param->philos[i].nb_meal < param->nb_of_eat)
		{
			pthread_mutex_unlock(&param->philos[i].nb_meal_m);
			return (0);
		}
		pthread_mutex_unlock(&param->philos[i].nb_meal_m);
		i++;
	}
	return (1);
}

int	ft_check_dinner(t_param *param, int i)
{
	int	j;

	j = 0;
	if (param->nb_of_eat && ft_dinner_end(param))
	{
		while (j < param->nb_phi)
		{
			pthread_mutex_lock(&param->philos[j].stop_m);
			param->philos[j].stop = 1;
			pthread_mutex_unlock(&param->philos[j].stop_m);
			pthread_mutex_unlock(&param->philos[j].fork);
			pthread_mutex_unlock(&param->philos[j].last_meal_m);
			j++;
		}
		pthread_mutex_lock(&param->msg_m);
		usleep(100);
		printf("%ld Dinner is over\n", ft_get_time()
			- param->philos[i].start_time);
		pthread_mutex_unlock(&param->msg_m);
		return (0);
	}
	return (1);
}

int	ft_monitoring(t_param *param)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < param->nb_phi)
		{
			if (!ft_check_death(param, i))
				return (0);
			if (!ft_check_dinner(param, i))
				return (0);
			i++;
		}
	}
}
