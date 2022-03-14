/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:49:00 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/14 10:49:40 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

void	ft_launch_process(t_param *param)
{
	int	i;

	i = -1;
	while (++i < param->nb_phi)
	{
		param->philos[i].pid = fork();
		if (param->philos[i].pid == 0)
			ft_philo(&param->philos[i]);
		if (param->philos[i].pid == -1)
			exit(EXIT_FAILURE);
	}
}

void	*ft_meal_monitor(void *data)
{
	t_param	*param;
	int		i;

	param = data;
	i = param->nb_phi;
	while (i-- > 0)
		sem_wait(param->sem_meal);
	sem_wait(param->sem_msg);
	printf("%ld Dinner is over\n", ft_get_time()
		- param->start_time);
	sem_post(param->sem_end);
	return (0);
}

int	ft_seek_n_destroy(t_param *param)
{
	int	i;

	i = -1;
	while (++i < param->nb_phi)
		kill(param->philos[i].pid, SIGKILL);
	sem_unlink(SEM_END);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_MSG);
	free(param->philos);
	return (0);
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
	ft_get_param(&param, av);
	ft_init_table(&param);
	ft_init_sem(&param);
	if (pthread_create(&param.meal_monitor, NULL, ft_meal_monitor, &param) != 0)
	{
		free(param.philos);
		exit(EXIT_FAILURE);
	}
	ft_launch_process(&param);
	sem_wait(param.sem_end);
	ft_seek_n_destroy(&param);
	return (0);
}
