/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmohamed <hmohamed@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:32:00 by hmohamed          #+#    #+#             */
/*   Updated: 2023/03/19 23:41:53 by hmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	psleep(t_thr *flo, long long time)
{
	long long	ctime;

	ctime = get_time();
	while (get_time() - ctime < time)
	{
		if (checkdead(flo))
			return (1);
		usleep(100);
	}
	return (0);
}

int	parc(int x, char **s, t_flo *fl)
{
	if (x == 5 || x == 6)
	{
		fl->nop = ft_atoi(s[1]);
		fl->ttd = ft_atoi(s[2]);
		fl->tte = ft_atoi(s[3]);
		fl->tts = ft_atoi(s[4]);
		fl->time = get_time();
		fl->alive = 0;
		if (x == 6)
			fl->notepme = ft_atoi(s[5]);
		else
			fl->notepme = INT_MAX;
	}
	else
	{
		write(2, "Error invalid number arqument\n", 30);
		return (1);
	}
	if (fl->nop > 200 || fl->nop == -1 || fl->notepme == -1
		|| fl->ttd == -1 || fl->tte == -1 || fl->tts == -1)
	{
		write(2, "Error invalid inputs\n", 21);
		return (1);
	}
	return (0);
}

void	*routine(void *h)
{
	t_thr	thre;

	thre = *(t_thr *)h;
	thre.fttd = thre.fl->ttd;
	thre.notep = thre.fl->notepme;
	forkdis(&thre);
	mutexdis(&thre);
	if (thre.fl->nop == 1)
	{
		psleep(&thre, thre.fttd + 100);
		return (0);
	}
	while (thre.notep != 0)
	{
		if (pickfork(&thre) || sleaping(&thre) || thinking(&thre))
			return (0);
		thre.notep--;
	}
	return (0);
}

void	excu(t_flo *fl)
{
	int		i;
	t_thr	*thr;

	i = 0;
	thr = malloc(fl->nop * sizeof(t_thr));
	fl->mutex = malloc(fl->nop * sizeof(pthread_mutex_t));
	mut_init(fl);
	while (i < fl->nop)
	{
		thr[i].index = i + 1;
		thr[i].fl = fl;
		if (pthread_create(&((thr[i]).th), NULL, &routine, &thr[i]) != 0)
			perror("Error");
		i++;
	}
	i = 0;
	while (i < fl->nop)
	{
		if (pthread_join(thr[i].th, NULL) != 0)
			perror("Error");
		i++;
	}
	mut_dest(fl);
	free(thr);
	free(fl->mutex);
}

int	main(int ac, char **av)
{
	t_flo	flo;
	int		p;

	p = parc(ac, av, &flo);
	if (p == 0)
	{
		flo.froks = malloc(flo.nop * sizeof(int));
		flo.frokss = malloc(flo.nop * sizeof(int));
		forksarr(&flo);
		excu(&flo);
		free(flo.froks);
		free(flo.frokss);
		return (0);
	}
	return (1);
}
