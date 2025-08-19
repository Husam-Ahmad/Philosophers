/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:40:38 by huahmad           #+#    #+#             */
/*   Updated: 2025/08/19 13:55:49 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)data_pointer;
	while (!get_dead(philo->data))
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->finished >= philo->data->num_philo)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->lock);
		usleep(1000);
	}
	return ((void *)0);
}

int	check_and_flag_finished(t_philo *philo)
{
	int	done;

	done = 0;
	pthread_mutex_lock(&philo->lock);
	if (philo->eat_cont == philo->data->num_meals)
	{
		philo->eat_cont++;
		done = 1;
	}
	pthread_mutex_unlock(&philo->lock);
	return (done);
}

void	*supervisor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_dead(philo->data))
	{
		if (check_and_handle_death(philo))
		{
			usleep(1000);
			continue ;
		}
		if (check_and_flag_finished(philo))
			mark_finished(philo);
		usleep(1000);
	}
	return (NULL);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	philo->time_to_die = get_time() + philo->data->time_die;
	if (pthread_create(&philo->t1, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (!get_dead(philo->data))
	{
		eat(philo);
		if (philo->data->num_philo != 1)
			messages("is thinking", philo);
	}
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	thread_init(t_data *data)
{
	int			i;

	data->start_time = get_time();
	i = -1;
	while (++i < data->num_philo)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (ft_error("creating threads error", data));
		ft_usleep(1);
	}
	i = -1;
	while (++i < data->num_philo)
	{
		if (pthread_join(data->tid[i], NULL) && data->num_philo != 1)
			return (ft_error("joining threads error", data));
	}
	return (0);
}
