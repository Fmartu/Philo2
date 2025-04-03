/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:02:12 by fmartusc          #+#    #+#             */
/*   Updated: 2025/03/31 16:19:45 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finalclean(t_all *all);

int	onlyonephilo(t_all *all)
{
	prints("has taken a fork", all, 0);
	ft_usleep(all->tdie);
	prints("has died", all, 0);
	pthread_mutex_lock(&all->lock);
	all->ko = 1;
	pthread_mutex_unlock(&all->lock);
	return (0);
}

void	end(t_all *all)
{
	int	i;

	pthread_mutex_lock(&all->lock);
	all->ko = 1;
	pthread_mutex_unlock(&all->lock);
	i = 0;
	while (i < all->nphilo)
	{
		pthread_mutex_destroy(&all->allforks[i]);
		pthread_mutex_destroy(&all->philo[i].plock);
		i++;
	}
}

int	error(t_all *all)
{
	if (all)
	{
		pthread_mutex_lock(&all->lock);
		all->ko = 1;
		pthread_mutex_unlock(&all->lock);
		end(all);
		pthread_mutex_destroy(&all->write);
		pthread_mutex_destroy(&all->lock);
		finalclean(all);
	}
	return (1);
}

void	finalclean(t_all *all)
{
	if (all->tnumber)
	{
		free(all->tnumber);
		all->tnumber = NULL;
	}
	if (all->allforks)
	{
		free(all->allforks);
		all->allforks = NULL;
	}
	if (all->philo)
	{
		free(all->philo);
		all->philo = NULL;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
