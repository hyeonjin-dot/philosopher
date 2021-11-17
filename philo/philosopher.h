/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:51:55 by hyejung           #+#    #+#             */
/*   Updated: 2021/11/06 18:49:17 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // thread
#include <unistd.h>
#include <sys/time.h>

struct	s_rule;

typedef struct	s_philo
{
	struct s_rule	*rule;
	int				id;
	int				left_fork;
	int				neat;
	long long		last_eat;
	pthread_t		thread;

}	t_philo;

typedef struct	s_rule
{
	int				pnum;
	int				die;
	int				eat;
	int				slp;
	int				neat;
	int				diephi;
	long long		startime;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
}	t_rule;

int			ft_atoi(const char *str);
int			init(t_rule *rule, char **argv);
int			init_philosopher(t_rule *rule);
int			init_mutex(t_rule *rule);
void		ft_destroy_mutex(t_rule *rule);
int			start(t_rule *rule);
void		ck_eat(t_philo *philo);//
void		ck_sleep(long long check, t_rule *rules);
void		*thread_start(void *philo);
void		print(t_rule *rules, int id, int i);
long long	timestamp(void);
long long	timecheck(long long past, long long now);

#endif
