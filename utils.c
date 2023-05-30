/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmohamed <hmohamed@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:48:55 by hmohamed          #+#    #+#             */
/*   Updated: 2023/03/19 20:28:35 by hmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	checkspace(char h)
{
	if (h == '\f' || h == '\t' || h == ' '
		|| h == '\n' || h == '\r' || h == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					c;
	unsigned long long	num;

	i = 0;
	c = 1;
	num = 0;
	while (str[i] != '\0' && checkspace(str[i]))
		i++;
	if (str == 0)
		return (0);
	if (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			c = -1;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (num > 2147483647 || c == -1 || num == 0)
		return (-1);
	return (c * num);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
}

void	printing(t_thr *flo, t_pets str)
{
	int		ptime;

	pthread_mutex_lock(&flo->fl->printing);
	ptime = get_time() - flo->fl->time;
	if (str == pdead && !flo->fl->alive)
	{
		pthread_mutex_lock(&flo->fl->fdist);
		flo->fl->alive = 1;
		pthread_mutex_unlock(&flo->fl->fdist);
		printf("[%d] philo %d is dead\n", ptime, flo->index);
		pthread_mutex_unlock(&flo->fl->printing);
		return ;
	}
	if (flo->fl->alive)
	{
		pthread_mutex_unlock(&flo->fl->printing);
		return ;
	}
	if (str == peating && !flo->fl->alive)
	{
		printf("[%d] philo %d is eating\n", ptime, flo->index);
		pthread_mutex_unlock(&flo->fl->printing);
	}
	exprinting(flo, str, ptime);
}

void	exprinting(t_thr *flo, t_pets str, int ptime)
{
	if (str == ptakefork && !flo->fl->alive)
	{
		printf("[%d] philo %d take the fork\n", ptime, flo->index);
		printf("[%d] philo %d take the fork\n", ptime, flo->index);
		pthread_mutex_unlock(&flo->fl->printing);
	}
	if (str == psleeping && !flo->fl->alive)
	{
		printf("[%d] philo %d is sleeping\n", ptime, flo->index);
		pthread_mutex_unlock(&flo->fl->printing);
	}
	if (str == pthinking && !flo->fl->alive)
	{
		printf("[%d] philo %d is thinking\n", ptime, flo->index);
		pthread_mutex_unlock(&flo->fl->printing);
	}
}
