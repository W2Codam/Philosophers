/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/17 12:27:38 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/17 12:36:55 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//= Utilization file for generic shit =//

#include "philo.h"

/**
 * Cleans up the game state.
 * 
 * @param state 
 */
void	ft_cleanup(t_state *state)
{
	int32_t	i;

	i = 0;
	pthread_mutex_destroy(&state->death_m);
	pthread_mutex_destroy(&state->print_m);
}

/**
 * Custom mutex locked printf.
 * Yeah not much here lol.
 * 
 * @param msg The message, can and only must have 2 '%d', 
 * one for timestamp other for id.
 * @param philo The philo.
 */
void	ft_mutex_print(const char *msg, t_philo *philo)
{
	const int64_t	time = ft_elapsed(philo->state->start_time);

	pthread_mutex_lock(&philo->state->print_m);
	if (philo->state->status == RUNNING)
		printf(msg, time, philo->id + 1);
	pthread_mutex_unlock(&philo->state->print_m);
}

/**
 * Prints a message to standard Error.
 *
 * @param msg The message.
 */
bool	ft_perror(const char *msg)
{
	int32_t	i;

	i = 0;
	while (msg[i])
		i++;
	write(STDERR_FILENO, msg, i);
	return (false);
}
