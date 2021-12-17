/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 13:01:19 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/17 12:33:55 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <memory.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_proccess
{
	RUNNING,
	FINISHED
}	t_process;

typedef struct s_state
{
	pthread_mutex_t		*forks;
	struct s_philo		*philos;

	pthread_mutex_t		print_m;
	pthread_mutex_t		death_m;

	int64_t				p_count;
	int64_t				eat_count;
	t_process			status;

	int64_t				start_time;
	int64_t				eating_time;
	int64_t				sleep_time;
	int64_t				death_time;
}	t_state;

typedef struct s_philo
{
	int32_t				id;
	pthread_t			thread;
	pthread_mutex_t		eat;

	int32_t				meals;
	int64_t				last_meal_time;

	t_state				*state;
}	t_philo;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING
}	t_status;

//= Philo =//

void	*ft_cycle(void *arg);
void	*ft_check_status(void *args);

// Utils =//

int64_t	ft_time(void);
void	ft_sleep(uint64_t ms);
int64_t	ft_elapsed(int64_t start);
bool	ft_perror(const char *msg);
void	ft_mutex_print(const char *msg, t_philo *philo);

#endif
