/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:18:13 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/10 17:14:08 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

int	ft_check_empty(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] != ' ' && av[i] != '\0')
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_format(char *av)
{
	int	i;

	i = 0;
	while (av[i] == ' ')
		i++;
	while (av[i] >= '0' && av[i] <= '9')
		i++;
	while (av[i] == ' ')
		i++;
	if (av[i] != '\0')
		return (0);
	return (1);
}

int	ft_check_args(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (ft_atoi(av[i]) > INT_MAX || ft_atoi(av[i]) < INT_MIN)
		{
			write (2, "Error : Int limit\n", 18);
			return (0);
		}
		if (ft_check_empty(av[i]) == TRUE)
		{
			write (2, "Error : Empty argument\n", 23);
			return (0);
		}
		if (ft_check_format(av[i]) == FALSE)
		{
			write (2, "Error : Wrong argument format\n", 30);
			return (0);
		}
		if ((i == 4 || i == 1) && ft_atoi(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_dinner_end(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->nb_phi)
	{
		pthread_mutex_lock(&param->philos[i].meal);
		if (param->philos[i].nb_meal < param->nb_of_eat)
		{
			pthread_mutex_unlock(&param->philos[i].meal);
			return (0);
		}
		pthread_mutex_unlock(&param->philos[i].meal);
		i++;
	}
	return (1);
}
