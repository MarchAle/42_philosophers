/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:49:00 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/09 14:40:17 by amarchal         ###   ########.fr       */
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
	if (!ft_init_table(&param))
		return (0);
	ft_init_sem(&param);
	if (pthread_create(&param.meal_monitor, NULL, ft_meal_monitor, &param) != 0)
	{
		free(param.philos);
		return (0);
	}
	ft_launch_process(&param);
	sem_wait(param.sem_end);
	ft_seek_n_destroy(&param);
	return (0);
}
