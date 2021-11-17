/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:51:25 by hyejung           #+#    #+#             */
/*   Updated: 2021/11/06 17:53:09 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    ck_eat(t_philo *philo)
{
    t_rule  	*new;
	int			left;
	int			nid;

	new = philo->rule;
	left = (philo)->left_fork;
	nid = (philo)->id;
	pthread_mutex_lock(&(new->fork[nid]));
	pthread_mutex_lock(&(new->fork[left]));
	print(new, philo->id, 0);
	print(new, philo->id, 1);
	if (timecheck(philo->last_eat, timestamp()) + new->eat > new->die)
	{
		while (timecheck(philo->last_eat, timestamp()) < new->die)
			usleep(100);
		new->diephi++;
		print(new, philo->id, 0);
	}
	else
		ck_sleep(new->eat, new);
	philo->last_eat = timestamp();
	philo->neat--;
	pthread_mutex_unlock(&(new->fork[nid]));
	pthread_mutex_unlock(&(new->fork[left]));
}

void	ck_sleep(long long check, t_rule *rules)
{
	long long	time;

	time = timestamp();
	while (rules->diephi == 0)
	{
		if (timecheck(time, timestamp()) >= (check))
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
