/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:17:51 by hyejung           #+#    #+#             */
/*   Updated: 2021/11/06 18:48:43 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_philosopher(t_rule *rule)
{
	int	i;

	i = rule->pnum;
	rule->philo = (t_philo *)malloc(sizeof(*(rule->philo)) * (rule->pnum));
	rule->fork = (pthread_mutex_t *)malloc(sizeof(*(rule->fork)) * (rule->pnum));
	while (--i >= 0)
	{
		rule->philo[i].id = i;
		if (i != 0)
			rule->philo[i].left_fork = i - 1;
		else
			rule->philo[i].left_fork = rule->pnum - 1;
		rule->philo[i].neat = rule->neat;
		rule->philo[i].rule = rule;
		rule->philo[i].last_eat = timestamp();
	}
	return (0);
}

int	init_mutex(t_rule *rule)
{
	int	i;

	i = rule->pnum;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rule->fork[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rule->print), NULL))
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
	rule->diephi = 0;
	init_philosopher(rule);
	init_mutex(rule);
	start(rule);
	return (0);
}
