/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:49:00 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/10 17:25:24 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

int	ft_get_param(t_param *param, char **av)
{
	param->nb_phi = ft_atoi(av[1]);
	// param->tempo = 100;
	// param->start_time = ft_get_time();
	if (param->nb_phi < 60)
		param->tempo = 100;
	else if (param->nb_phi < 120)
		param->tempo = 500;
	else
		param->tempo = 1000;
	param->t_die = ft_atoi(av[2]);
	param->t_eat = ft_atoi(av[3]);
	param->t_sleep = ft_atoi(av[4]);
	if (av[5])
		param->nb_of_eat = ft_atoi(av[5]);
	else
		param->nb_of_eat = 0;
	// if (pthread_mutex_init(&param->msg, NULL))
	// 	return (0);
	return (1);
}

int	ft_init_table(t_param *param)
{
	int		i;
	t_philo	philo;

	i = 0;
	param->philos = malloc(sizeof(t_philo) * param->nb_phi);
	if (!param->philos)
		return (0);
	while (i < param->nb_phi)
	{
		philo.index = i + 1;
		// philo.fork_lock = 0;
		philo.p = param;
		philo.last_meal = 0;
		philo.nb_meal = 0;
		// philo.dead = 0;
		philo.stop = 0;
		philo.color = (i + 1) % 8 + 90;
		param->philos[i] = philo;
		if (pthread_mutex_init(&param->philos[i].fork, NULL)
			|| pthread_mutex_init(&param->philos[i].stop_m, NULL)
			|| pthread_mutex_init(&param->philos[i].last_meal_m, NULL)
			|| pthread_mutex_init(&param->philos[i].meal, NULL))
			return (0);
		i++;
	}
	return (1);
}

int	ft_monitoring(t_param *param)
{
	int	i;
	int	j;

	j = 0;
	while (1)
	{
		i = 0;
		while (i < param->nb_phi)
		{
			// pthread_mutex_lock(&param->philos[j].last_meal_m);
			if (ft_get_time() >= param->philos[i].last_meal + param->t_die)
			{
				while (j < param->nb_phi)
				{
					pthread_mutex_lock(&param->philos[j].stop_m);
					param->philos[j].stop = 1;
					pthread_mutex_unlock(&param->philos[j].stop_m);
					pthread_mutex_unlock(&param->philos[j].fork);
					j++;
				}
				printf("%ld %d died\n", ft_get_time() - param->philos[i].start_time, param->philos[i].index);
				// pthread_mutex_unlock(&param->philos[j].last_meal_m);
				return (0);
			}
			// pthread_mutex_unlock(&param->philos[j].last_meal_m);
			if (param->nb_of_eat && ft_dinner_end(param))
			{
				while (j < param->nb_phi)
				{
					pthread_mutex_lock(&param->philos[j].stop_m);
					param->philos[j].stop = 1;
					pthread_mutex_unlock(&param->philos[j].stop_m);
					pthread_mutex_unlock(&param->philos[j].fork);
					j++;
				}
				printf("%ld Dinner is over\n", ft_get_time() - param->philos[i].start_time);
				return (0);
			}
			i++;
		}	
		// usleep(100);
	}
}

int	ft_launch_thread(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->nb_phi)
	{
		if (pthread_create(&param->philos[i].thread, NULL,
				ft_philo, &param->philos[i]) != 0)
			return (0);
		i++;
	}
	usleep(100);
	ft_monitoring(param);
	i = 0;
	while (i < param->nb_phi)
	{
		if (pthread_join(param->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_param	param;

	if (ac < 5 || ac > 6)
	{
		write (2, "Error : Wrong number of arguments\n", 34);
		return (0);
	}
	if (ft_check_args(&av[1]) == FALSE)
		return (0);
	if (!ft_get_param(&param, av) || !ft_init_table(&param))
		return (0);
	if (!ft_launch_thread(&param))
		return (0);
	ft_mutex_destroy(&param);
	free(param.philos);
	return (0);
}
