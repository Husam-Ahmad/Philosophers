/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:46:56 by huahmad           #+#    #+#             */
/*   Updated: 2025/08/18 12:13:28 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	 one_philo(t_data *data)
{
	pthread_mutex_lock(&data->print);
	printf("philo->data->dead: %d\n", data->dead);
	pthread_mutex_unlock(&data->print);
	data->start_time = get_time();
	eat(data->philos);
	pthread_create(&data->tid[0], NULL, &supervisor, &data->philos[0]);
	pthread_detach(data->tid[0]);
	while (data->dead == 0)
		ft_usleep(1);
	ft_exit(data);
	return (0);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->lock);
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

int	ft_error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || 6 < ac)
	{
		ft_error("argc is less than 5 or more than 6", NULL);
		return (1);
	}
	if (check_input_is_number(av))
	{
		ft_error("input is not a positive int", NULL);
		return (1);
	}
	if (init(&data, av))
		return (1);
	if (data.num_philo == 1)
		return (one_philo(&data));
	if (thread_init(&data))
		return (1);
	ft_exit(&data);
	return (0);
}
