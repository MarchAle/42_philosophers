/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:02:28 by amarchal          #+#    #+#             */
/*   Updated: 2022/02/23 16:12:11 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/philo.h"

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

long	ft_get_time(void)
{
	struct timeval	time;
	long			ms;
	
	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	return (ms);
}