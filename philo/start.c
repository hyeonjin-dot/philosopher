/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:46:17 by hyejung           #+#    #+#             */
/*   Updated: 2021/11/13 21:09:40 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_destroy_mutex(t_rule *rule)
{
    int i;

	i = rule->pnum;
	while (--i >= 0)
		pthread_join((rule->philo[i].thread), NULL);
	i = rule->pnum;
	while (--i >= 0)
		pthread_mutex_destroy(&(rule->fork[i]));
	free(rule->philo);
	free(rule->fork);
}

void	*thread_start(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->id % 2 == 1)
		usleep(500);
	usleep(philo->id * 10);
	while (philo->rule->diephi == 0)
	{
		ck_eat(ph);
		if (philo->neat == 0)
			break ;
		print(philo->rule, philo->id, 2);
		ck_sleep(philo->rule->slp, philo->rule);
		print(philo->rule, philo->id, 3);
	}
	return (0);
}

int	start(t_rule *rule)
{
	t_philo	*ph;
	int		i;

	i = 0;
	ph = rule->philo;
	rule->startime = timestamp();
	while (i < rule->pnum)
	{
		if (pthread_create(&(ph[i].thread), NULL, thread_start, (void *)&(ph[i])))
			return (1);
		i++;
	}
	ft_destroy_mutex(rule);
	return (0);
}

void	print(t_rule *rule, int id, int num)
{
	pthread_mutex_lock(&(rule->print));
	printf("timestamp in %lldms\t", timecheck(rule->startime, timestamp()));
	if (rule->diephi < 1)
	{
		if (num == 0)
		{
			if (id == 0)
				printf("%d has taken forks %d and %d\n", id + 1, rule->pnum, id + 1);
			else
				printf("%d has taken forks %d and %d\n", id + 1, id, id + 1);
		}
		else if (num == 1)
			printf("%d is eating\n", id + 1);
		else if (num == 2)
			printf("%d is sleeping\n", id + 1);
		else
			printf("%d is thinking\n", id + 1);
	}
	if (rule->diephi == 1)
		printf("%d died\n", id + 1);
	if (rule->diephi == 1)
		rule->diephi++;
	pthread_mutex_unlock(&rule->print);
}
