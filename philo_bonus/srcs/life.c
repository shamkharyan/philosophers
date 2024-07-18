/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:44:53 by pshamkha          #+#    #+#             */
/*   Updated: 2024/07/17 19:57:36 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	think(t_philo *p)
{
	ft_putmsg(p, "is thinking", GRN);
	sem_wait(p->check_sem);
	p->last_action = THINK;
	sem_post(p->check_sem);
}

static void	zzz(t_philo *p)
{
	ft_putmsg(p, "is sleeping", BLU);
	sem_wait(p->check_sem);
	p->last_action = SLEEP;
	sem_post(p->check_sem);
	ft_sleep(p->args->sleep_time);
}

static void	eat(t_philo *p)
{
	if (p->args->count == 1)
	{
		sem_wait(p->forks);
		ft_putmsg(p, "has taken a fork", YEL);
		ft_sleep(p->args->die_time + 1);
		sem_post(p->forks);
	}
	else
	{
		sem_wait(p->forks);
		ft_putmsg(p, "has taken a fork", YEL);
		sem_wait(p->forks);
		ft_putmsg(p, "has taken a fork", YEL);
		ft_putmsg(p, "is eating", RED);
		sem_wait(p->check_sem);
		p->last_action = EAT;
		p->last_eat = get_time();
		p->eat_count++;
		sem_post(p->check_sem);
		ft_sleep(p->args->eat_time);
		sem_post(p->forks);
		sem_post(p->forks);
	}
}

void	*life(void *data)
{
	t_philo	*p;

	p = (t_philo *) data;
	pthread_create(&p->monitor, NULL, monitor, (void *) p);
	pthread_detach(p->monitor);
	if (p->id % 2 == 0)
		ft_sleep(1);
	while (1)
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
