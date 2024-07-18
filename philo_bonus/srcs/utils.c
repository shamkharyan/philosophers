/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:49:12 by pshamkha          #+#    #+#             */
/*   Updated: 2024/07/18 18:19:18 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (0);
	}
	return (1000 * time.tv_sec + time.tv_usec / 1000);
}

short	ft_atos(char *str)
{
	int	num;

	num = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = 10 * num + *str - '0';
		if (num > SHRT_MAX)
			return (0);
		str++;
	}
	if (*str == '\0')
		return ((short) num);
	return (0);
}

void	ft_putmsg(t_philo *p, char	*msg, const char *color)
{
	sem_wait(p->msg_sem);
	printf("%s%lums %d %s\n%s", color, get_time() - *p->start_time,
		p->id, msg, RES);
	sem_post(p->msg_sem);
}

void	ft_sleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
}

void	free_memory(t_prog *p)
{
	int	i;

	i = -1;
	while (++i < p->args.count)
		kill(p->philos[i].pid, SIGKILL);
	sem_close(p->forks);
	sem_close(p->end_sem);
	sem_close(p->check_sem);
	sem_close(p->msg_sem);
	free(p->philos);
}
