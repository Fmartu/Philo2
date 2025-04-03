/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:10:37 by fmartusc          #+#    #+#             */
/*   Updated: 2025/04/03 17:05:15 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	t_all	all;

	if (!av[1])
		return (makeitgay(2));
	all.tstart = 0;
	if (checkerinput(ac, av) == 1)
		return (0);
	if (ac == 6 && (ft_atoi(av[5]) == 0))
		return (0);
	memset(&all, 0, sizeof(t_all));
	initall(&all, ac, av);
	all.tstart = get_time();
	if (all.nphilo == 1)
		onlyonephilo(&all);
	else if (tinit((&all), -1))
		return (1);
	pthread_mutex_lock(&all.lock);
	all.ko = 1;
	pthread_mutex_unlock(&all.lock);
	end(&all);
	pthread_mutex_destroy(&all.write);
	pthread_mutex_destroy(&all.lock);
	finalclean(&all);
	return (0);
}
