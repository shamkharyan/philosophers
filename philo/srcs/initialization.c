/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:58:15 by pshamkha          #+#    #+#             */
/*   Updated: 2024/07/03 18:13:37 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static int	mutexes_init(t_prog *p)
{
	int	i;

	p->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * p->args.count);
	if (p->forks == NULL)
		return (0);
	i = 0;
	while (i < p->args.count)
		if (pthread_mutex_init(&p->forks[i++], NULL))
			return (0);
	if (pthread_mutex_init(&p->check_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&p->end_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&p->msg_mutex, NULL))
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
		p->philos[i].left = &p->forks[i];
		p->philos[i].args = &p->args;
		p->philos[i].proc_end = &p->proc_end;
		p->philos[i].last_eat = p->start_time;
		p->philos[i].start_time = &p->start_time;
		p->philos[i].end_mutex = &p->end_mutex;
		p->philos[i].check_mutex = &p->check_mutex;
		p->philos[i].msg_mutex = &p->msg_mutex;
		p->philos[i].last_action = THINK;
		p->philos[i].right = &p->forks[0];
		if (i + 1 < p->args.count)
			p->philos[i].right = &p->forks[i + 1];
	}
	return (1);
}

int	prog_init(t_prog *p, int argc, char **argv)
{
	p->proc_end = 0;
	if (!args_init(p, argc, argv) || !mutexes_init(p) || !philos_init(p))
		return (0);
	return (1);
}
