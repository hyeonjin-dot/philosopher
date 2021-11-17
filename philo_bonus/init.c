/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:17:51 by hyejung           #+#    #+#             */
/*   Updated: 2021/11/17 19:42:44 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_philosopher(t_rule *rule)
{
	int	i;

	i = rule->pnum;
	rule->philo = (t_philo *)malloc(sizeof(*(rule->philo)) * i);
	while (--i >= 0)
	{
		rule->philo[i].id = i;
		rule->philo[i].neat = rule->neat;
		rule->philo[i].rule = rule;
		rule->philo[i].last_eat = timestamp();
	}
	return (0);
}

int	init_mutex(t_rule *rule)
{
	sem_unlink("/num_sem");
	sem_unlink("/test_sem");
	rule->fork = sem_open("/num_sem", O_CREAT, S_IRWXU, rule->pnum);
	if (rule->fork <= 0)
		return (1);
	rule->print = sem_open("/test_sem", O_CREAT, S_IRWXU, 1);
	if (rule->print <= 0)
		return (1);
	return (0);
}

int	init(t_rule *rule, char **argv)
{
	rule->pnum = ft_atoi(argv[1]);
	rule->die = ft_atoi(argv[2]);
	rule->eat = ft_atoi(argv[3]);
	rule->slp = ft_atoi(argv[4]);
	if (rule->pnum <= 1)
		return (0);
	if (argv[5])
		rule->neat = ft_atoi(argv[5]);
	else
		rule->neat = -1;
	if (rule->die <= 0 || rule->eat <= 0 || rule->slp <= 0)
		return (0);
	rule->diephi = 0;
	init_philosopher(rule);
	init_mutex(rule);
	start(rule);
	return (0);
}
