/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:41:54 by huahmad           #+#    #+#             */
/*   Updated: 2025/08/19 13:42:12 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_dead(t_data *d)
{
	int	v;

	pthread_mutex_lock(&d->lock);
	v = d->dead;
	pthread_mutex_unlock(&d->lock);
	return (v);
}

void	mark_finished(t_philo *p)
{
	pthread_mutex_lock(&p->data->lock);
	p->data->finished++;
	if (p->data->finished == p->data->num_philo)
		p->data->dead = 1;
	pthread_mutex_unlock(&p->data->lock);
}

int	check_and_handle_death(t_philo *philo)
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