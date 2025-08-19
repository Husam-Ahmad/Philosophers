/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:42:15 by huahmad           #+#    #+#             */
/*   Updated: 2025/08/19 12:43:48 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_cont;
	int				eating;
	unsigned int	time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*rightfork;
	pthread_mutex_t	*leftfork;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				num_philo;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	int				num_meals;
	int				dead;
	int				finished;
	unsigned int	start_time;
	pthread_t		*tid;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	print;
}	t_data;

int				ft_atoi(const char *str);
int				ft_error(char *str, t_data *data);
int				ft_strcmp(char *s1, char *s2);
void			messages(char *str, t_philo *philo);
void			ft_exit(t_data *data);
int				ft_usleep(unsigned int time);
int				init(t_data *data, char **av);
int				thread_init(t_data *data);
int				check_input_is_number(char **av);
int				get_dead(t_data *d);
void			eat(t_philo *philo);
void			mark_finished(t_philo *p);
int				check_and_handle_death(t_philo *philo);
int				check_and_flag_finished(t_philo *philo);
void			*supervisor(void *philo_pointer);
void			*routine(void *philo_pointer);
int				ft_av_check(char **str);
unsigned int	get_time(void);

#endif