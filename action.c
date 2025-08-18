/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:08:36 by huahmad           #+#    #+#             */
/*   Updated: 2025/08/18 12:59:40 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_error("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (unsigned int)1000) + (tv.tv_usec / 1000));
}

void	messages(char *str, t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print);
	time = get_time() - philo->data->start_time;
	if (ft_strcmp("DIED", str) == 0 && philo->data->dead == 0)
	{
		printf("%lld %d %s\n", time, philo->id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%lld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
}

void take_forks(t_philo *p) 
{
    if (p->id % 2 == 0) 
	{
        pthread_mutex_lock(p->leftfork);  
		messages("has taken a fork", p);
        pthread_mutex_lock(p->rightfork); 
		messages("has taken a fork", p);
    } 
	else 
	{
        pthread_mutex_lock(p->rightfork); 
		messages("has taken a fork", p);
        pthread_mutex_lock(p->leftfork);  
		messages("has taken a fork", p);
    }
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->leftfork);
	pthread_mutex_unlock(philo->rightfork);
	messages("is sleeping", philo);
	ft_usleep(philo->data->time_sleep);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	if (philo->data->num_philo != 1)
		messages("is eating", philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->data->time_die;
	philo->eat_cont++;
	ft_usleep(philo->data->time_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	if (philo->data->num_philo != 1)
		drop_forks(philo);
}