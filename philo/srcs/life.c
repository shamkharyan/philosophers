/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:44:53 by pshamkha          #+#    #+#             */
/*   Updated: 2024/07/03 19:27:45 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *p)
{
	ft_putmsg(p, "is thinking", GRN);
	pthread_mutex_lock(p->check_mutex);
	p->last_action = THINK;
	pthread_mutex_unlock(p->check_mutex);
}

static void	zzz(t_philo *p)
{
	ft_putmsg(p, "is sleeping", BLU);
	pthread_mutex_lock(p->check_mutex);
	p->last_action = SLEEP;
	pthread_mutex_unlock(p->check_mutex);
	ft_sleep(p->args->sleep_time);
}

static void	eat(t_philo *p)
{
	if (p->args->count == 1)
	{
		pthread_mutex_lock(p->left);
		ft_putmsg(p, "has taken a fork", YEL);
		ft_sleep(p->args->die_time + 1);
		pthread_mutex_unlock(p->left);
	}
	else
	{
		pthread_mutex_lock(p->left);
		ft_putmsg(p, "has taken a fork", YEL);
		pthread_mutex_lock(p->right);
		ft_putmsg(p, "has taken a fork", YEL);
		ft_putmsg(p, "is eating", RED);
		pthread_mutex_lock(p->check_mutex);
		p->last_action = EAT;
		p->last_eat = get_time();
		p->eat_count++;
		pthread_mutex_unlock(p->check_mutex);
		ft_sleep(p->args->eat_time);
		pthread_mutex_unlock(p->left);
		pthread_mutex_unlock(p->right);
	}
}

void	*life(void *data)
{
	t_philo	*p;

	p = (t_philo *) data;
	if (p->id % 2 == 0)
		ft_sleep(1);
	while (!check_proc_end(p))
	{
		if (p->last_action == THINK)
			eat(p);
		if (p->last_action == EAT)
			zzz(p);
		if (p->last_action == SLEEP)
			think(p);
	}
	return (NULL);
}
