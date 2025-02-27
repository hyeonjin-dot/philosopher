/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:51:25 by hyejung           #+#    #+#             */
/*   Updated: 2021/11/17 18:49:35 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	die_ck(t_philo *philo, t_rule *new)
{
	if (new->eat > new->die)
	{
		while (timecheck(philo->last_eat, timestamp()) < new->die)
			usleep(100);
		print(new, 0, "died");
		new->diephi = 2;
	}
	else if (timecheck(philo->last_eat, timestamp()) + new->eat > new->die)
	{
		sem_wait(new->dieck);
		while (timecheck(philo->last_eat, timestamp()) < new->die)
			usleep(100);
		new->diephi++;
		print(new, philo->id, "die");
		sem_post(new->dieck);
	}
}

void	ck_eat(t_philo *philo)
{
	t_rule		*new;
	int			nid;

	new = philo->rule;
	nid = philo->id;
	sem_wait(new->fork);
	sem_wait(new->fork);
	print(new, philo->id, "has taken a fork");
	print(new, philo->id, "has taken a fork");
	print(new, philo->id, "is eating");
	if (new->eat > new->die || timecheck(philo->last_eat, timestamp()) + new->eat > new->die)
		die_ck(philo, new);
	else
		ck_sleep(new->eat, new);
	philo->last_eat = timestamp();
	philo->neat--;
	sem_post(new->fork);
	sem_post(new->fork);
}

void	ck_sleep(long long check, t_rule *rules)
{
	long long	time;

	time = timestamp();
	while (rules->diephi == 0)
	{
		if (timecheck(time, timestamp()) >= check)
			break ;
		usleep(500);
	}
}

int	main(int argc, char **argv)
{
	t_rule	rule;

	if (argc < 5)
		return (0);
	init(&rule, argv);
	return (0);
}