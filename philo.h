/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:37:04 by fmartusc          #+#    #+#             */
/*   Updated: 2025/04/03 17:26:51 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define GREEN "\033[1;32m"
# define PINK "\033[1;35m"
# define BLUE "\033[1;34m"
# define YELLOW "\033[1;33m"
# define RED "\033[1;31m"
# define R "\033[0m"

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_all	t_all;

typedef struct s_philo
{
	int					number;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
	long long			tlasteat;
	int					nmeals;
	long long int		willdie;
	int					status;
	int					eatstatus;
	pthread_t			t;
	pthread_t			*slay;
	pthread_mutex_t		plock;
	t_all				*all;
}						t_philo;

typedef struct s_all
{
	int					nphilo;
	int					tdie;
	int					teat;
	int					tsleep;
	long long int		tstart;
	int					nmaxmeals;
	pthread_mutex_t		*allforks;
	pthread_mutex_t		lock;
	pthread_mutex_t		write;
	pthread_t			*tnumber;
	int					ko;
	int					ok;
	int					death_printed;
	t_philo				*philo;
}						t_all;

long long int			ft_atoi(const char *str);
int						checkerinput(int ac, char **av);
void					initall(t_all *all, int ac, char **av);
long long int			get_time(void);
void					prints(char *str, t_all *all, int philo_num);
void					ft_usleep(u_int64_t milliseconds);
void					end(t_all *all);
int						tinit(t_all *all, int i);
int						onlyonephilo(t_all *all);
void					*monitor(void *data_pointer);
int						error(t_all *all);
void					*routine(void *philo_pointer);
int						ft_strcmp(const char *s1, const char *s2);
void					eat(t_all *all, int i);
void					finalclean(t_all *all);
int						makeitgay(int n);
char					*setcolor(char *str);
void					setok(t_all *all);
void					setexit(t_all *all, int *should_exit);

#endif