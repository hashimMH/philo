/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmohamed <hmohamed@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:32:49 by hmohamed          #+#    #+#             */
/*   Updated: 2023/03/20 15:49:53 by hmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_flo
{
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				notepme;
	long long		time;
	int				alive;
	int				*froks;
	int				*frokss;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	fdist;
	pthread_mutex_t	h;
	pthread_mutex_t	printing;
}	t_flo;

typedef struct s_thr
{
	pthread_mutex_t	*forkr;
	pthread_mutex_t	*forkl;
	int				*fright;
	int				*fleft;
	int				*frights;
	int				*flefts;
	int				notep;
	int				index;
	int				fttd;
	pthread_t		th;
	t_flo			*fl;
}	t_thr;

typedef enum s_pets
{
	ptakefork,
	peating,
	psleeping,
	pthinking,
	pdead,
}	t_pets;

int			ft_atoi(const char *str);
long long	get_time(void);
int			pickfork(t_thr *thre);
int			eating(t_thr *thre);
int			sleaping(t_thr *flo);
int			thinking(t_thr *flo);
int			checkdead(t_thr *flo);
void		printing(t_thr *flo, t_pets str);
void		exprinting(t_thr *flo, t_pets str, int ptime);
int			psleep(t_thr *flo, long long time);
void		forkdis(t_thr *flo);
void		mutexdis(t_thr *thre);
void		forkdiss(t_thr *flo);
void		forksarr(t_flo *flo);
int			readfork(t_thr *flo);
int			readforks(t_thr *flo);
void		mut_init(t_flo *flo);
void		mut_dest(t_flo *flo);
void		lock_init(t_thr *thre);

#endif