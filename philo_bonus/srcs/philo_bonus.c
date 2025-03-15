/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamkharyan <shamkharyan@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:01:47 by pshamkha          #+#    #+#             */
/*   Updated: 2025/03/15 19:45:05 by shamkharyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start(t_prog *p)
{
	int	i;

	i = -1;
	while (++i < p->args.count)
	{
		p->philos[i].pid = fork();
		if (p->philos[i].pid == 0)
		{
			life(&p->philos[i]);
			exit(EXIT_SUCCESS);
		}
	}
}

int	main(int argc, char **argv)
{
	t_prog	p;

	if (prog_init(&p, argc, argv))
	{
		start(&p);
		waitpid(-1, NULL, 0);
		free_memory(&p);
	}
	else
		write(2, "Error\n", 6);
	return (0);
}
