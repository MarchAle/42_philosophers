/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:13:50 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/07 13:06:21 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define SEM_NAME "/sem_exemple"

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

void	ft_test(int pid, sem_t *semaphore)
{
	// sem_t	*semaphore;
	
	// sem_unlink(SEM_NAME);
	// semaphore = sem_open(SEM_NAME, O_RDWR);
	while(1)
	{
		sem_wait(semaphore);
		printf("Je suis pid : %d, sem -1 \n", pid);
		sleep(1);
	}
}

int	main(int ac, char **av)
{
	sem_t	*semaphore;
	int		pid = 0;
	int		i = 0;
	
	sem_unlink(SEM_NAME);
	semaphore = sem_open(SEM_NAME, O_CREAT, 644, ft_atoi(av[2]));
	// sem_close(semaphore);
	while (i < ft_atoi(av[1]) && pid == 0)
	{
		usleep(100);
		pid = fork();
		i++;
	}
	if (pid != 0)
	{
		ft_test(pid, semaphore);
	}
	// while (1)
	// {
	// 	sem_wait(semaphore);
	// 	printf("sem -1 \n");
	// 	sleep(1);
	// }
	(void)ac;
}