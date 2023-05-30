/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rout.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmohamed <hmohamed@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:04:37 by hmohamed          #+#    #+#             */
/*   Updated: 2023/03/20 16:31:49 by hmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pickfork(t_thr *thre)
{
	while (readfork(thre))
	{
		if (psleep(thre, 2))
			return (1);
	}
	while (readforks(thre))
	{
		if (psleep(thre, 2))
			return (1);
	}
	pthread_mutex_lock(thre->forkl);
	pthread_mutex_lock(thre->forkr);
	lock_init(thre);
	printing(thre, ptakefork);
	eating(thre);
	pthread_mutex_unlock(thre->forkl);
	pthread_mutex_unlock(thre->forkr);
	return (0);
}

int	eating(t_thr *thre)
{
	int	ptime;

	if (checkdead(thre))
		return (1);
	ptime = get_time() - thre->fl->time;
	thre->fttd = ptime + thre->fl->ttd;
	printing(thre, peating);
	if (psleep(thre, thre->fl->tte))
		return (1);
	pthread_mutex_lock(&thre->fl->h);
	*thre->frights = 0;
	pthread_mutex_unlock(&thre->fl->h);
	pthread_mutex_lock(&thre->fl->h);
	*thre->flefts = 0;
	pthread_mutex_unlock(&thre->fl->h);
	return (0);
}

int	sleaping(t_thr *flo)
{
	if (checkdead(flo))
		return (1);
	printing(flo, psleeping);
	if (psleep(flo, flo->fl->tts))
		return (1);
	return (0);
}

int	thinking(t_thr *flo)
{
	if (checkdead(flo))
		return (1);
	printing(flo, pthinking);
	return (0);
}

int	checkdead(t_thr *flo)
{
	int	ptime;

	pthread_mutex_lock(&flo->fl->fdist);
	if (flo->fl->alive)
	{
		pthread_mutex_unlock(&flo->fl->fdist);
		return (1);
	}
	pthread_mutex_unlock(&flo->fl->fdist);
	ptime = get_time() - flo->fl->time;
	if (ptime >= flo->fttd)
	{
		printing(flo, pdead);
		return (1);
	}
	return (0);
}
