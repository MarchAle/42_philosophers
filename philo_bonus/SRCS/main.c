/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:49:00 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/08 18:13:49 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

void	ft_init_sem(t_param *param)
{
	sem_t	*semaphore;
	sem_t	*sem_dead;
	sem_t	*sem_meal;
	
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_MEAL);
	semaphore = sem_open(SEM_FORK, O_CREAT | O_EXCL, 644, param->nb_phi);
	sem_dead = sem_open(SEM_DEAD, O_CREAT | O_EXCL, 644, 0);
	sem_meal = sem_open(SEM_MEAL, O_CREAT | O_EXCL, 644, 0);
	param->semaphore = semaphore;
	param->sem_dead = sem_dead;
	param->sem_meal = sem_meal;
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
		philo.p = param;
		philo.last_meal = 0;
		philo.nb_meal = 0;
		philo.color = (i + 1) % 8 + 90;
		param->philos[i] = philo;
		i++;
	}
	return (1);
}

void	ft_launch_process(t_param *param)
{
	int i;
	int pid;

	i = 0;
	pid = 0;
	while (i < param->nb_phi)
	{
		param->philos[i].pid = fork();
		if (param->philos[i].pid == 0)
			ft_philo(&param->philos[i]);
		i++;
		usleep(100);
	}
}

void	*ft_meal_monitor(void *data)
{
	t_param	*param;
	int		i;

	param = data;

	i = param->nb_phi;
	while (i > 0)
	{
		sem_wait(param->sem_meal);
		printf("sem_wait\n");
		i--;
	}
	// i = 0;
	// while (1)
	// {
	// 	printf("sem_wait %d\n", i);
	// 	sem_wait(param->sem_meal);
	// 	i++;
		
	// }
	printf("BOUM !\n");
	sem_post(param->sem_dead);
	return (0);
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
	ft_init_sem(&param);
	if (pthread_create(&param.meal_monitor, NULL, ft_meal_monitor, &param) != 0)
		return (0);
	ft_launch_process(&param);
	i = 0;
	// sem_wait(param.sem_meal);
	sem_wait(param.sem_dead);
	while (i < param.nb_phi)
	{
		kill(param.philos[i].pid, SIGKILL);
		i++;
	}
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_MEAL);
	free(param.philos);
	return (0);
}
