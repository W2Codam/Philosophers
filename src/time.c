/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 13:00:40 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/17 12:29:39 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//= Utilization file for time fuckery =//

#include "philo.h"

/**
 * Returns the time in milliseconds.
 *
 * @note Because the gettimeofday struct seems to be
 * designed by literal morons.
 *
 * @return The current time expressed in milliseconds.
 */
int64_t	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec) * 1000) + ((time.tv_usec) / 1000));
}

/**
 * Given a start time, find how many ms have passed since then.
 *
 * @param start The starting time.
 * @return The number of ticks/ms that have passed since start.
 */
int64_t	ft_elapsed(int64_t start)
{
	return (ft_time() - start);
}

/**
 * Ensures exact sleep amount given in ms.
 *
 * @note So the problem here is that usleep does not promise to actually
 * sleep until ms but rather up-to ms and then just quits too soon.
 *
 * @param ms Sleep the current thread for x amount, expressed in milliseconds.
 */
void	ft_sleep(uint64_t ms)
{
	uint64_t	time;

	time = ft_time();
	while ((ft_time() - time) < ms)
		usleep(100);
}
