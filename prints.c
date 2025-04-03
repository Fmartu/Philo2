/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:03:51 by fmartusc          #+#    #+#             */
/*   Updated: 2025/04/03 17:26:59 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(u_int64_t milliseconds)
{
	u_int64_t	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < milliseconds)
		usleep(50);
}

long long int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (long long int)1000) + (tv.tv_usec / 1000));
}

char	*setcolor(char *str)
{
	if (ft_strcmp(str, "has taken a fork") == 0)
		return (GREEN);
	else if (ft_strcmp(str, "is eating") == 0)
		return (PINK);
	else if (ft_strcmp(str, "is sleeping") == 0)
		return (BLUE);
	else if (ft_strcmp(str, "is thinking") == 0)
		return (YELLOW);
	else if (ft_strcmp(str, "has died") == 0)
		return (RED);
	else
		return (R);
}

void	prints(char *str, t_all *all, int philo_num)
{
	long long int	time;
	char			*color;
	int				should_print;

	should_print = 1;
	pthread_mutex_lock(&all->lock);
	if (all->ko && ft_strcmp("has died", str) != 0)
		should_print = 0;
	else if (ft_strcmp("has died", str) == 0)
	{
		if (all->death_printed)
			should_print = 0;
		else
			all->death_printed = 1;
	}
	pthread_mutex_unlock(&all->lock);
	if (!should_print)
		return ;
	pthread_mutex_lock(&all->write);
	time = get_time() - all->tstart;
	color = setcolor(str);
	printf("%lld %d %s%s%s\n", time, philo_num + 1, color, str, R);
	pthread_mutex_unlock(&all->write);
}
