/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:46:56 by huahmad           #+#    #+#             */
/*   Updated: 2025/08/18 17:42:14 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_data *data)
{
    t_philo	*p;

	p = &data->philos[0];
    data->start_time = get_time();
    messages("has taken a fork", p);
    pthread_mutex_lock(&p->lock);
    p->eating = 0;
    p->time_to_die = get_time() + data->time_die;
    pthread_mutex_unlock(&p->lock);
    if (pthread_create(&p->t1, NULL, &supervisor, p))
        return ft_error("creating supervisor error", data);
    if (pthread_join(p->t1, NULL))
        return ft_error("joining supervisor error", data);
    ft_exit(data);
    return 0;
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
