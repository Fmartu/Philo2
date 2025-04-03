/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartusc <fmartusc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:36:54 by fmartusc          #+#    #+#             */
/*   Updated: 2025/03/31 18:28:25 by fmartusc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	numchk(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

long long int	ft_atoi(const char *str)
{
	int				i;
	int				sig;
	long long int	res;

	i = 0;
	sig = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sig = -1;
		i++;
	}
	if (numchk((char *)&str[i]) == 1)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sig);
}

int	makeitgay(int n)
{
	if (n == 1)
	{
		printf("\033[1;33m🍜 Error: wrong number of numbers\033[0m\n");
		return (1);
	}
	if (n == 2)
	{
		printf("\033[1;33m🍜 Error: ... nice try, missing arguments\033[0m\n");
		return (1);
	}
	return (0);
}

int	checkerinput(int ac, char **av)
{
	int				i;
	long long int	value;

	i = 1;
	value = ft_atoi(av[i]);
	if (ac != 5 && ac != 6)
		return (makeitgay(1));
	while (i < ac)
	{
		if (numchk(av[i]) != 0)
		{
			printf("\033[1;33m🍜 Error: Argument %d is not valid\033[0m\n", i);
			return (1);
		}
		value = ft_atoi(av[i]);
		if (value > 2147483647)
		{
			printf("\033[1;33m🍜 Error: Argument %d out of scope\033[0m\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}
