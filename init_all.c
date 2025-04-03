/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:38:14 by fmartusc          #+#    #+#             */
/*   Updated: 2025/03/31 16:30:58 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initphilo(t_all *all);
void	initfork(t_all *all);

void	initall(t_all *all, int ac, char **av)
{
	memset(all, 0, sizeof(t_all));
	if (pthread_mutex_init(&all->lock, NULL) != 0
		|| pthread_mutex_init(&all->write, NULL) != 0)
		return ;
	pthread_mutex_lock(&all->lock);
	all->nphilo = ft_atoi(av[1]);
	all->tdie = ft_atoi(av[2]);
	all->teat = ft_atoi(av[3]);
	all->tsleep = ft_atoi(av[4]);
	if (ac == 6)
		all->nmaxmeals = ft_atoi(av[5]);
	else
		all->nmaxmeals = -1;
	all->ko = 0;
	all->ok = 0;
	all->death_printed = 0;
	pthread_mutex_unlock(&all->lock);
	if (all->nphilo <= 0 || all->tdie < 0 || all->teat < 0 || all->tsleep < 0)
		return ;
	initphilo(all);
	initfork(all);
}

void	initfork(t_all *all)
{
	int	i;

	all->allforks = malloc(sizeof(pthread_mutex_t) * all->nphilo);
	if (!all->allforks)
		return ;
	i = 0;
	while (i < all->nphilo)
	{
		pthread_mutex_init(&all->allforks[i], NULL);
		i++;
	}
	i = 0;
	while (i < all->nphilo)
	{
		all->philo[i].lfork = &all->allforks[i];
		all->philo[i].rfork = &all->allforks[(i + 1) % all->nphilo];
		i++;
	}
	return ;
}

void	initphilo(t_all *all)
{
	int	i;

	i = 0;
	all->philo = malloc(sizeof(t_philo) * all->nphilo);
	if (!all->philo)
		return ;
	while (i < all->nphilo)
	{
		all->philo[i].number = i;
		all->philo[i].tlasteat = 0;
		all->philo[i].nmeals = 0;
		all->philo[i].status = 0;
		all->philo[i].eatstatus = 0;
		all->philo[i].willdie = 0;
		all->tstart = 0;
		all->philo[i].all = all;
		pthread_mutex_init(&all->philo[i].plock, NULL);
		i++;
	}
}

int	retprint(t_all *all)
{
	printf("Thread 🕷️ \033[1;31merror\033[0m\n");
	return (error(all));
}

int	tinit(t_all *all, int i)
{
	pthread_t	tr;

	all->tnumber = malloc(sizeof(pthread_t) * all->nphilo);
	if (!all->tnumber)
		return (error(all));
	if (all->nmaxmeals > 0)
		if (pthread_create(&tr, NULL, &monitor, all))
			return (retprint(all));
	while (++i < all->nphilo)
	{
		all->philo[i].number = i;
		pthread_mutex_lock(&all->lock);
		if (pthread_create(&all->tnumber[i], NULL, &routine, &all->philo[i]))
			return (retprint(all));
		pthread_mutex_unlock(&all->lock);
	}
	i = -1;
	while (++i < all->nphilo)
		if (all->tnumber && all->tnumber[i])
			if (pthread_join(all->tnumber[i], NULL))
				return (retprint(all));
	if (all->nmaxmeals > 0)
		pthread_detach(tr);
	return (0);
}
