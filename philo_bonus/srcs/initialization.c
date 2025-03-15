/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamkharyan <shamkharyan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:58:15 by pshamkha          #+#    #+#             */
/*   Updated: 2025/03/15 19:45:36 by shamkharyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	args_init(t_prog *p, int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		p->args.count = ft_atos(argv[1]);
		p->args.die_time = ft_atos(argv[2]);
		p->args.eat_time = ft_atos(argv[3]);
		p->args.sleep_time = ft_atos(argv[4]);
		p->args.eat_count = -1;
		if (argc == 6)
			p->args.eat_count = ft_atos(argv[5]);
		return (!(p->args.count == 0 || p->args.count > 200
				|| p->args.die_time < 60 || p->args.eat_time < 60
				|| p->args.sleep_time < 60 || p->args.eat_count == 0));
	}
	return (0);
}

static int	semes_init(t_prog *p)
{
	sem_unlink("/forks");
	sem_unlink("/end");
	sem_unlink("/msg");
	sem_unlink("/check");
	p->msg_sem = sem_open("/msg", O_CREAT, 0644, 1);
	if (p->msg_sem == SEM_FAILED)
		return (0);
	p->check_sem = sem_open("/check", O_CREAT, 0644, 1);
	if (p->check_sem == SEM_FAILED)
		return (0);
	p->forks = sem_open("/forks", O_CREAT, 0644, p->args.count);
	if (p->forks == SEM_FAILED)
		return (0);
	return (1);
}

static int	philos_init(t_prog *p)
{
	int		i;

	p->philos = (t_philo *) malloc(sizeof(t_philo) * p->args.count);
	if (p->philos == NULL)
		return (0);
	i = -1;
	p->start_time = get_time();
	while (++i < p->args.count)
	{
		p->philos[i].id = i + 1;
		p->philos[i].eat_count = 0;
		p->philos[i].args = &p->args;
		p->philos[i].proc_end = &p->proc_end;
		p->philos[i].last_eat = p->start_time;
		p->philos[i].start_time = &p->start_time;
		p->philos[i].check_sem = p->check_sem;
		p->philos[i].msg_sem = p->msg_sem;
		p->philos[i].forks = p->forks;
		p->philos[i].last_action = THINK;
	}
	return (1);
}

int	prog_init(t_prog *p, int argc, char **argv)
{
	p->proc_end = 0;
	if (!args_init(p, argc, argv) || !semes_init(p) || !philos_init(p))
		return (0);
	return (1);
}
