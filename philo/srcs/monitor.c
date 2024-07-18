/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:54:28 by pshamkha          #+#    #+#             */
/*   Updated: 2024/07/03 18:31:51 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_one_dead(t_philo *p)
{
	pthread_mutex_lock(p->check_mutex);
	if ((short)(get_time() - p->last_eat) > p->args->die_time
		&& p->last_action != EAT)
	{
		pthread_mutex_unlock(p->check_mutex);
		return (1);
	}
	pthread_mutex_unlock(p->check_mutex);
	return (0);
}

static int	check_dead(t_prog *p)
{
	size_t	time;
	int		i;

	time = get_time();
	i = -1;
	while (++i < p->args.count)
	{
		if (check_one_dead(&p->philos[i]))
		{
			ft_putmsg(&p->philos[i], "died", RES);
			pthread_mutex_lock(&p->end_mutex);
			p->proc_end = 1;
			pthread_mutex_unlock(&p->end_mutex);
			return (1);
		}
	}
	return (0);
}

static int	check_eat_count(t_prog *p)
{
	int	i;

	i = -1;
	if (p->args.eat_count == -1)
		return (0);
	while (++i < p->args.count)
	{
		pthread_mutex_lock(&p->check_mutex);
		if (p->philos[i].eat_count < p->args.eat_count)
			return (pthread_mutex_unlock(&p->check_mutex), 0);
		pthread_mutex_unlock(&p->check_mutex);
	}
	pthread_mutex_lock(&p->end_mutex);
	p->proc_end = 1;
	pthread_mutex_unlock(&p->end_mutex);
	return (1);
}

void	*monitor(void *data)
{
	t_prog	*p;

	p = (t_prog *) data;
	while (1)
	{
		if (check_dead(p) || check_eat_count(p))
			break ;
	}
	return (NULL);
}

int	check_proc_end(t_philo *p)
{
	int	flag;

	pthread_mutex_lock(p->end_mutex);
	flag = *p->proc_end;
	pthread_mutex_unlock(p->end_mutex);
	return (flag);
}
