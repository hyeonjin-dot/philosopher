/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:46:17 by hyejung           #+#    #+#             */
/*   Updated: 2021/11/17 19:37:07 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_destroy_mutex(t_rule *rule)
{
	int	i;

	i = rule->pnum;
	while (--i >= 0)
		pthread_join((rule->philo[i].thread), NULL);
	free(rule->philo);
	sem_close(rule->fork);
	sem_close(rule->print);
	sem_unlink("/num_sem");
	sem_unlink("/test_sem");
}

void	*th_start(void *ph)
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
		print(philo->rule, philo->id, "is sleeping");
		ck_sleep(philo->rule->slp, philo->rule);
		print(philo->rule, philo->id, "is thinking");
		usleep(10);
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
		if (pthread_create(&(ph[i].thread), NULL, th_start, (void *)&(ph[i])))
			return (1);
		i++;
	}
	ft_destroy_mutex(rule);
	return (0);
}

void	print(t_rule *rule, int id, char *string)
{
	sem_wait(rule->print);
	if (rule->diephi < 1)
	{
		printf("%lldms\t", timecheck(rule->startime, timestamp()));
		printf("%d ", id + 1);
		printf("%s\n", string);
	}
	if (rule->diephi == 1)
	{
		printf("%lldms\t", timecheck(rule->startime, timestamp()));
		printf("%d died\n", id + 1);
		rule->diephi++;
	}
	sem_post(rule->print);
	return ;
}
