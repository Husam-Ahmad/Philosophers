/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:40:38 by huahmad           #+#    #+#             */
/*   Updated: 2025/08/19 12:37:23 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) data_pointer;
	pthread_mutex_lock(&philo->data->print);
	printf("philo->data->dead: %d\n", philo->data->dead);
	pthread_mutex_unlock(&philo->data->print);
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->finished >= philo->data->num_philo)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->lock);
	}
	return ((void *)0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <you@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:00:00 by yourlogin         #+#    #+#             */
/*   Updated: 2025/08/19 00:00:00 by yourlogin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	get_dead(t_data *d)
{
	int	v;

	pthread_mutex_lock(&d->lock);
	v = d->dead;
	pthread_mutex_unlock(&d->lock);
	return (v);
}

static void	mark_finished(t_philo *p)
{
	pthread_mutex_lock(&p->data->lock);
	p->data->finished++;
	if (p->data->finished == p->data->num_philo)
		p->data->dead = 1;
	pthread_mutex_unlock(&p->data->lock);
}

static int	check_and_handle_death(t_philo *philo)
{
	uint64_t	now;

	pthread_mutex_lock(&philo->lock);
	now = get_time();
	if (!philo->eating && now >= philo->time_to_die)
	{
		messages("DIED", philo);
		pthread_mutex_unlock(&philo->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

static int	check_and_flag_finished(t_philo *philo)
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
	while (philo->data->dead == 0)
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
	pthread_t	t0;

	data->start_time = get_time();
	if (data->num_meals > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &data->philos[0]))
			return (ft_error("creating threads error", data));
		pthread_detach(t0);
	}
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
