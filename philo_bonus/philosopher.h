/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:51:55 by hyejung           #+#    #+#             */
/*   Updated: 2021/11/17 19:36:33 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h> 
# include <sys/ipc.h> 
# include <sys/sem.h>
# include <semaphore.h>

struct	s_rule;

typedef struct s_philo
{
	struct s_rule	*rule;
	int				id;
	int				neat;
	long long		last_eat;
	pthread_t		thread;
}	t_philo;

typedef struct s_rule
{
	int				pnum;
	int				die;
	int				eat;
	int				slp;
	int				neat;
	int				diephi;
	long long		startime;
	t_philo			*philo;
	sem_t			*fork;
	sem_t			*print;
}	t_rule;

int			ft_atoi(const char *str);
int			init(t_rule *rule, char **argv);
int			init_philosopher(t_rule *rule);
int			init_mutex(t_rule *rule);
void		ft_destroy_mutex(t_rule *rule);
int			start(t_rule *rule);
void		ck_eat(t_philo *philo);
void		ck_sleep(long long check, t_rule *rules);
void		*th_start(void *philo);
void		print(t_rule *rules, int id, char *string);//int i
long long	timestamp(void);
long long	timecheck(long long past, long long now);

#endif
