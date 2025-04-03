/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitorutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:15:58 by fmartusc          #+#    #+#             */
/*   Updated: 2025/04/03 17:24:06 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setexit(t_all *all, int *should_exit)
{
	pthread_mutex_lock(&all->lock);
	*should_exit = all->ko;
	pthread_mutex_unlock(&all->lock);
}

void	setok(t_all *all)
{
	pthread_mutex_lock(&all->lock);
	all->ok++;
	pthread_mutex_unlock(&all->lock);
}
