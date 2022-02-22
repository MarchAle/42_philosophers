#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_data
{
	pthread_mutex_t	mutex;
	char			*str1;
	char			*str2;
	int				x;
}	t_data;

void	*ft_first(void *arg)
{
	int	i = 0;

	pthread_mutex_lock(&((t_data *)arg)->mutex);
	while (i < 15)
	{
		usleep(50000);
		printf("avt x = %d\n", ((t_data *)arg)->x);
		printf("\033[92m%s\033[0m\n", ((t_data *)arg)->str1);
		((t_data *)arg)->x = 11;
		printf("apr x = %d\n", ((t_data *)arg)->x);
		i++;
	}
	pthread_mutex_unlock(&((t_data *)arg)->mutex);
	return (((t_data *)arg)->str1);
}

void	*ft_second(void *arg)
{
	int	i = 0;

	pthread_mutex_lock(&((t_data *)arg)->mutex);
	while (i < 10)
	{
		usleep(50000);
		printf("avt x = %d\n", ((t_data *)arg)->x);
		printf("\033[94m%s\033[0m\n", ((t_data *)arg)->str2);
		((t_data *)arg)->x = 22;
		printf("apr x = %d\n", ((t_data *)arg)->x);
		i++;
	}
	pthread_mutex_unlock(&((t_data *)arg)->mutex);
	return (((t_data *)arg)->str2);
}

int	main(int ac, char **av)
{
	void	*result1;
	void	*result2;
	t_data	data;

	data.str1 = "Hello";
	data.str2 = "Aurevoir";
	data.x = 55;
	pthread_mutex_init(&data.mutex, NULL);
	result1 = NULL;
	result2 = NULL;
	pthread_t	firstthread;
	pthread_t	secondthread;
	pthread_create(&firstthread, NULL, ft_first, &data);
	pthread_create(&secondthread, NULL, ft_second, &data);
	pthread_join(firstthread, &result1);
	pthread_join(secondthread, &result2);
	printf ("%s et %s ont été print\n", (char *)result1, (char *)result2);
	pthread_mutex_destroy(&data.mutex);
	(void)ac;
	(void)av;
	return (0);
}