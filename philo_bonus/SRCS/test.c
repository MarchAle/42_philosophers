/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:56:08 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/04 14:00:01 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_param
{
	// sem_t		*semaphore;
	int			forks;
	int			nb_phi;
	long		t_die;
	long		t_eat;
	long		t_sleep;
	int			nb_of_eat;
	// t_philo		*philos;
	int			tempo;
}	t_param;

long int	ft_atoi(const char *str)
{
	int			i;
	long int	number;

	i = 0;
	number = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number *= 10;
		number += str[i++] - 48;
	}
	return (number);
}

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
		if (ft_check_empty(av[i]) == 1)
		{
			write (2, "Error : Empty argument\n", 23);
			return (0);
		}
		if (ft_check_format(av[i]) == 0)
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

void	ft_test(int pid, int i, int *pids, int nbrphilo)
{
	printf("Hello je suis philo %d avec le pid %d\n", i, pid);
	pids[i - 1] = pid;
	int j = 0;
	while (j < nbrphilo)
	{
		printf("pids[%d] = %d\n", j, pids[j]);
		j++;
	}
}

int	main(int ac, char **av)
{
	t_param	param;
	int	pid = 0;
	int nbr;
	int	*pids;

	if (ac < 5 || ac > 6)
	{
		write (2, "Error : Wrong number of arguments\n", 34);
		return (0);
	}
	if (ft_check_args(&av[1]) == 0)
		return (0);
	if (ft_atoi(av[1]) == 1)
	{
		printf("\033[91m%ld ms 1 died\033[0m\n", ft_atoi(av[2]));
		return (0);
	}
	ft_get_param(&param, av);
	nbr = ft_atoi(av[1]);
	pids = malloc(sizeof(int) * nbr);
	while (nbr > 0 && pid == 0)
	{
		pid = fork();
		nbr--;
	}
	printf("ici pid = %d et nbr = %d\n", pid, nbr);
	// pids[nbr] = pid;
	if (pid != 0)
		ft_test(pid, nbr + 1, pids, ft_atoi(av[1]));

		
	if (pid == 0)
	{
		sleep(1);
		int j = 0;
		while (j < ft_atoi(av[1]))
		{
			printf("pids[%d] = %d\n", j, pids[j]);
			j++;
		}
	}
}