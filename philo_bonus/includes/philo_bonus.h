/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshamkha <pshamkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:17:32 by pshamkha          #+#    #+#             */
/*   Updated: 2024/07/18 16:33:05 by pshamkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H

# include <unistd.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <signal.h>

# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define BLU "\x1B[34m"
# define YEL "\x1B[33m"
# define RES "\x1B[0m"

typedef enum s_action
{
	EAT,
	SLEEP,
	THINK
}	t_action;

typedef struct s_args
{
	short			count;
	short			die_time;
	short			sleep_time;
	short			eat_time;
	short			eat_count;
}	t_args;

typedef struct s_philo
{
	pthread_t	monitor;
	pid_t		pid;
	sem_t		*forks;
	sem_t		*end_sem;
	sem_t		*check_sem;
	sem_t		*msg_sem;
	size_t		last_eat;
	size_t		*start_time;
	short		id;
	short		eat_count;
	short		last_action;
	short		*proc_end;
	t_args		*args;
}	t_philo;

typedef struct s_prog
{
	t_args		args;
	short		proc_end;
	size_t		start_time;
	t_philo		*philos;
	sem_t		*forks;
	sem_t		*end_sem;
	sem_t		*check_sem;
	sem_t		*msg_sem;
}	t_prog;

short	ft_atos(char *str);
size_t	get_time(void);
void	ft_putmsg(t_philo *p, char	*msg, const char *color);
void	ft_sleep(size_t milliseconds);
int		prog_init(t_prog *p, int argc, char **argv);
void	*monitor(void *data);
void	*life(void *data);
void	start(t_prog *p);
void	free_memory(t_prog *p);

#endif
