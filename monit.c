/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:07:00 by fmartusc          #+#    #+#             */
/*   Updated: 2025/04/03 17:32:18 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checkdeath(t_philo *philo, t_all *all, long long current_time)
{
	char			*c;
	long long int	t;

	pthread_mutex_lock(&philo->plock);
	current_time = get_time();
	if (current_time >= philo->willdie && philo->eatstatus == 0)
	{
		pthread_mutex_unlock(&philo->plock);
		pthread_mutex_lock(&all->lock);
		if (!all->death_printed)
		{
			all->ko = 1;
			all->death_printed = 1;
			pthread_mutex_unlock(&all->lock);
			pthread_mutex_lock(&all->write);
			t = get_time() - all->tstart;
			c = setcolor("has died");
			printf("%lld %d %s%s%s\n", t, philo->number + 1, c, "has died", R);
			pthread_mutex_unlock(&all->write);
		}
		else
			pthread_mutex_unlock(&all->lock);
		return (0);
	}
	return (1);
}

void	*checkphilo(void *singlephilo)
{
	t_philo	*philo;
	t_all	*all;
	int		local_meals;
	int		should_exit;

	should_exit = 0;
	philo = (t_philo *)singlephilo;
	all = philo->all;
	while (!should_exit)
	{
		setexit(all, &should_exit);
		if (should_exit)
			break ;
		if (checkdeath(philo, all, 0) == 0)
			break ;
		local_meals = philo->nmeals;
		if (all->nmaxmeals > 0 && local_meals >= all->nmaxmeals)
		{
			pthread_mutex_unlock(&philo->plock);
			setok(all);
			break ;
		}
		pthread_mutex_unlock(&philo->plock);
	}
	return (NULL);
}

void	*monitor(void *data_pointer)
{
	t_all	*all;
	int		philo_count;

	all = (t_all *)data_pointer;
	while (1)
	{
		pthread_mutex_lock(&all->lock);
		if (all->ko == 1)
		{
			pthread_mutex_unlock(&all->lock);
			break ;
		}
		philo_count = all->ok;
		if (philo_count >= all->nphilo)
		{
			all->ko = 1;
			pthread_mutex_unlock(&all->lock);
			break ;
		}
		pthread_mutex_unlock(&all->lock);
	}
	return ((void *)0);
}

static void	monitloop(t_all *all, int i)
{
	int	should_exit;

	should_exit = 0;
	while (!should_exit)
	{
		pthread_mutex_lock(&all->lock);
		should_exit = all->ko;
		pthread_mutex_unlock(&all->lock);
		if (should_exit)
			break ;
		eat(all, i);
		prints("is thinking", all, i);
		ft_usleep(4);
	}
	return ;
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;
	t_all	*all;
	int		i;

	philo = (t_philo *)philo_pointer;
	all = philo->all;
	i = philo->number;
	pthread_mutex_lock(&philo->plock);
	philo->willdie = get_time() + all->tdie;
	pthread_mutex_unlock(&philo->plock);
	if (pthread_create(&philo->t, NULL, &checkphilo, philo))
		return ((void *)1);
	monitloop(all, i);
	if (pthread_join(philo->t, NULL))
		return ((void *)1);
	return ((void *)0);
}
