/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:18:35 by hyejung           #+#    #+#             */
/*   Updated: 2021/11/02 13:46:19 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	checkspace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	else
		return (0);
}

int	return_num(int count, int minus, int num)
{
	if (count >= 20 && minus == 1)
		return (-1);
	else if (count >= 20 && minus != 1)
		return (0);
	else
		return (minus * num);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	num;
	int	count;

	i = 0;
	num = 0;
	count = 0;
	minus = 1;
	while ((str[i] != '\0') && (checkspace((char)str[i]) == 1))
		i++;
	if ((char)str[i] == '-')
		minus = -1;
	if ((char)str[i] == '+' || minus == -1)
		i++;
	while ((char)str[i] >= '0' && (char)str[i] <= '9' && str[i])
	{
		num = (num * 10) + ((char)str[i++] - '0');
		count++;
	}
	return (return_num(count, minus, num));
}

long long	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	timecheck(long long past, long long now)
{
	return (now - past);
}
