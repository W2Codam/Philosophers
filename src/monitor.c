/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 14:14:32 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/16 22:40:00 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//= The monitor, aka The harbinger of death. =//

#include "philo.h"

/**
 * The harbingers job, checks if any philos die.
 * If they do indeed die it will check first if its because
 * they managed ot finish to eat their meals.
 * 
 * If so, gg!
 * 
 * @param state The current game state. 
 * @return True if nobody died, false if somebody did die.
 */
static bool	ft_check(t_state *state)
{
	int32_t	i;
	t_philo	*philo;
	int64_t	time;

	i = -1;
	while (++i < state->p_count)
	{
		philo = &state->philos[i];
		time = ft_time() - philo->last_meal_time;
		if (time > state->death_time)
		{
			state->status = FINISHED;
			if (philo->meals != 0)
			{
				printf("\033[31m[%lld] | [%d]: Is dead 💀!!!!\n\e[0m", \
				ft_elapsed(philo->state->start_time), philo->id + 1);
			}
			return (false);
		}
	}
	return (true);
}

/**
 * Monitor entry point; This is where the harbinger of death resides.
 * 
 * @param args The current game state.
 * @return Absolutely fuck all.
 */
void	*ft_check_status(void *args)
{
	while (ft_check((t_state *)args))
		usleep(100);
	return (NULL);
}
