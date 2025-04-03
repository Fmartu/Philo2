/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eatforks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:39:31 by fmartusc          #+#    #+#             */
/*   Updated: 2025/03/31 17:57:28 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pfork(char c, t_all *all, int i)
{
	if (c == 'l')
	{
		pthread_mutex_lock(all->philo[i].lfork);
		prints("has taken a fork", all, i);
	}
	else if (c == 'r')
	{
		pthread_mutex_lock(all->philo[i].rfork);
		prints("has taken a fork", all, i);
	}
	else if (c == 'd')
	{
		pthread_mutex_unlock(all->philo[i].lfork);
		pthread_mutex_unlock(all->philo[i].rfork);
		prints("is sleeping", all, i);
		ft_usleep(all->tsleep);
	}
	else
	{
		printf("\033[1;31mError, deadlock 🤼\033[0m\n");
		error(all);
	}
}

void	forkstuff(char c, t_all *all, int i)
{
	if (c == 't')
	{
		if (all->nphilo == 1)
		{
			pfork('l', all, i);
			ft_usleep(all->tdie);
			return ;
		}
		if (i % 2 != 0)
		{
			pfork('l', all, i);
			pfork('r', all, i);
		}
		else
		{
			pfork('r', all, i);
			pfork('l', all, i);
		}
	}
	else if (c == 'd')
		pfork('d', all, i);
}

void	eat(t_all *all, int i)
{
	if (all->philo[i].number % 2 != 1)
		usleep(10);
	forkstuff('t', all, i);
	pthread_mutex_lock(&all->philo[i].plock);
	all->philo[i].eatstatus = 1;
	all->philo[i].willdie = get_time() + all->tdie;
	all->philo[i].tlasteat = get_time();
	pthread_mutex_unlock(&all->philo[i].plock);
	prints("is eating", all, i);
	pthread_mutex_lock(&all->philo[i].plock);
	all->philo[i].nmeals++;
	pthread_mutex_unlock(&all->philo[i].plock);
	ft_usleep(all->teat);
	pthread_mutex_lock(&all->philo[i].plock);
	all->philo[i].eatstatus = 0;
	pthread_mutex_unlock(&all->philo[i].plock);
	forkstuff('d', all, i);
}
