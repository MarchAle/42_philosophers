/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:18:13 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/08 17:49:28 by amarchal         ###   ########.fr       */
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
		if (i == 4 && ft_atoi(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

// int	ft_check_meal(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo->p->nb_phi)
// 	{
// 		if (philo->p->philos[i].nb_meal < philo->p->nb_of_eat)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

void	ft_check_meal(t_philo *philo)
{
	if (philo->nb_meal == philo->p->nb_of_eat)
	{
		printf("%d a bien mangé\n", philo->index);
		sem_post(philo->p->sem_meal);
	}
}
