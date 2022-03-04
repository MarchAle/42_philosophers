/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:49:00 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/04 17:37:55 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

void	ft_get_param(t_param *param, char **av)
{
	param->nb_phi = ft_atoi(av[1]);
	param->semafork = sem_open("/semafork", O_CREAT | O_EXCL, 0644, param->nb_phi);
	sem_close(param->semafork);
	// sem_open(&param->semafork, 0, param->nb_phi);
	// sem_open()
	param->forks = param->nb_phi;
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
		// philo.fork_lock = 0;
		philo.p = param;
		philo.last_meal = 0;
		philo.nb_meal = 0;
		philo.dead = 0;
		philo.color = (i + 1) % 8 + 90;
		param->philos[i] = philo;
		// if (pthread_mutex_init(&param->philos[i].fork, NULL) != 0)
		// 	return (0);
		i++;
	}
	return (1);
}

// int	ft_launch_thread(t_param *param)
// {
// 	int	i;

// 	i = 0;
// 	while (i < param->nb_phi)
// 	{
// 		usleep(10);
// 		if (pthread_create(&param->philos[i].thread, NULL,
// 				ft_philo, &param->philos[i]) != 0)
// 			return (0);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < param->nb_phi)
// 	{
// 		if (pthread_join(param->philos[i].thread, NULL) != 0)
// 			return (0);
// 		i++;
// 	}
// 	sem_unlink(param->semaphore);
// 	// ft_mutex_destroy(param);
// 	free(param->philos);
// 	return (1);
// }

void	ft_test(int pid, int i, t_param *param)
{
	printf("Hello je suis philo %d avec le pid %d\n", i, pid);
	param->pids[i - 1] = pid;
	// int j = 0;
	// usleep(100000 * i);
	// while (j < param->nb_phi)
	// {
	// 	printf("pids[%d] = %d\n", j, param->pids[j]);
	// 	j++;
	// }
}

int	main(int ac, char **av)
{
	t_param	param;
	int		i;
	int		pid;

	i = 0;
	pid = 0;
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
	param.semafork = sem_open(SEM_NAME, O_RDWR, 0644, param.nb_phi);	
	param.pids = malloc(sizeof(int) * param.nb_phi);
	while (i < param.nb_phi && pid == 0)
	{
		usleep(100);
		param.pids[i] = fork();
		pid = param.pids[i];
		i++;
	}
	// printf("ici pid = %d et nbr = %d\n", pid, i);
	// pids[nbr] = pid;
	if (pid != 0)
	{
		ft_philo(pid, i, &param);
		// ft_test(pid, i, &param);
	}

	// if (pid == 0)
	// {
	// 	int j = 0;
	// 	while (j < param.nb_phi)
	// 	{
	// 		printf("pids[%d] = %d\n", j, param.pids[j]);
	// 		j++;
	// 	}
	// }
	return (0);
}
