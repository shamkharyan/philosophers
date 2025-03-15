/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamkharyan <shamkharyan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:54:28 by pshamkha          #+#    #+#             */
/*   Updated: 2025/03/15 19:46:04 by shamkharyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_dead(t_philo *p)
{
	sem_wait(p->check_sem);
	if ((short)(get_time() - p->last_eat) > p->args->die_time
		&& p->last_action != EAT)
	{
		ft_putmsg(p, "died", RES);
		sem_post(p->check_sem);
		return (1);
	}
	sem_post(p->check_sem);
	return (0);
}

static int	check_eat_count(t_philo *p)
{
	sem_wait(p->check_sem);
	if (p->args->eat_count == -1)
		return (sem_post(p->check_sem), 0);
	if (p->eat_count <= p->args->eat_count)
		return (sem_post(p->check_sem), 0);
	sem_post(p->check_sem);
	return (1);
}

void	*monitor(void *data)
{
	t_philo	*p;

	p = (t_philo *) data;
	while (1)
	{
		if (check_dead(p) || check_eat_count(p))
			break ;
	}
	exit(EXIT_SUCCESS);
	return (NULL);
}
