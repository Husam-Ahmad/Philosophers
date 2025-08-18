/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:58:50 by huahmad           #+#    #+#             */
/*   Updated: 2025/08/16 16:13:08 by huahmad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	val;

	neg = 1;
	i = 0;
	val = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		neg = -neg;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		val = val * 10 + str[i] - '0';
		i++;
	}
	return (val * neg);
}

int	check_input_is_number(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if ((av[i][j] < '0' || av[i][j] > '9'))
				return (1);
	}
	return (0);
}

int	ft_usleep(unsigned int time)
{
	unsigned int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_av_check(char **str)
{
	int	a;
	int	b;
	int	c;
	int	d;
	int	e;

 	a = ft_atoi(str[1]);
	b = ft_atoi(str[2]);
	c = ft_atoi(str[3]);
	d = ft_atoi(str[4]);
	if (str[5])
		e = ft_atoi(str[5]);
	else
		e = 1;
	if (a <= 0 || b <= 0 || c <= 0 || d <= 0 || e <= 0)
		return (1);
	return (0);
}