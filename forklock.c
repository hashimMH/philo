/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forklock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmohamed <hmohamed@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:16:27 by hmohamed          #+#    #+#             */
/*   Updated: 2023/03/20 16:39:17 by hmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	readforks(t_thr *flo)
{
	int	i;
	int	j;

	pthread_mutex_lock(&flo->fl->h);
	i = *flo->frights;
	pthread_mutex_unlock(&flo->fl->h);
	pthread_mutex_lock(&flo->fl->h);
	j = *flo->flefts;
	pthread_mutex_unlock(&flo->fl->h);
	if (i != 0 || j != 0)
		return (1);
	return (0);
}

int	readfork(t_thr *flo)
{
	int	i;
	int	j;

	pthread_mutex_lock(&flo->fl->h);
	i = *flo->fright;
	pthread_mutex_unlock(&flo->fl->h);
	pthread_mutex_lock(&flo->fl->h);
	j = *flo->fleft;
	pthread_mutex_unlock(&flo->fl->h);
	if (i == flo->index || j == flo->index)
		return (1);
	return (0);
}

void	mut_init(t_flo *flo)
{
	int	i;

	i = 0;
	while (i < flo->nop)
	{
		pthread_mutex_init(&flo->mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&flo->h, NULL);
	pthread_mutex_init(&flo->fdist, NULL);
	pthread_mutex_init(&flo->printing, NULL);
}

void	mut_dest(t_flo *flo)
{
	int	i;

	i = 0;
	while (i < flo->nop)
	{
		pthread_mutex_destroy(&flo->mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&flo->printing);
	pthread_mutex_destroy(&flo->fdist);
	pthread_mutex_destroy(&flo->h);
}

void	lock_init(t_thr *thre)
{
	pthread_mutex_lock(&thre->fl->h);
	*thre->fright = thre->index;
	pthread_mutex_unlock(&thre->fl->h);
	pthread_mutex_lock(&thre->fl->h);
	*thre->fleft = thre->index;
	pthread_mutex_unlock(&thre->fl->h);
	pthread_mutex_lock(&thre->fl->h);
	*thre->frights = thre->index;
	pthread_mutex_unlock(&thre->fl->h);
	pthread_mutex_lock(&thre->fl->h);
	*thre->flefts = thre->index;
	pthread_mutex_unlock(&thre->fl->h);
}
