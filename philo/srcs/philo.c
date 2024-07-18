/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:24:55 by pshamkha          #+#    #+#             */
/*   Updated: 2024/07/04 13:30:01 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start(t_prog *p)
{
	int	i;

	pthread_create(&p->monitor, NULL, monitor, (void *) p);
	i = -1;
	while (++i < p->args.count)
		pthread_create(&p->philos[i].thread, NULL,
			life, (void *) &p->philos[i]);
	i = -1;
	pthread_join(p->monitor, NULL);
	while (++i < p->args.count)
		pthread_join(p->philos[i].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_prog	p;

	if (prog_init(&p, argc, argv))
	{
		start(&p);
		free_memory(&p);
	}
	else
		write(2, "Error\n", 6);
	return (0);
}
