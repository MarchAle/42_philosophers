/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:49:00 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/01 17:08:05 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

void	ft_get_param(t_param *param, char **av)
{
	param->nb_phi = ft_atoi(av[1]);
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
		philo.fork_lock = 0;
		philo.p = param;
		philo.last_meal = 0;
		philo.nb_meal = 0;
		philo.dead = 0;
		philo.color = (i + 1) % 8 + 90;
		param->philos[i] = philo;
		if (pthread_mutex_init(&param->philos[i].fork, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_launch_thread(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->nb_phi)
	{
		usleep(10);
		if (pthread_create(&param->philos[i].thread, NULL,
				ft_philo, &param->philos[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < param->nb_phi)
	{
		if (pthread_join(param->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	ft_mutex_destroy(param);
	free(param->philos);
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
	if (ft_atoi(av[1]) == 1)
	{
		printf("\033[91m%ld ms 1 died\033[0m\n", ft_atoi(av[2]));
		return (0);
	}
	ft_get_param(&param, av);
	if (!ft_init_table(&param))
		return (0);
	if (!ft_launch_thread(&param))
		return (0);
	return (0);
}
