/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 13:00:42 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/17 12:36:41 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//= The life of a philospher can be seen here =//

#include "philo.h"

/**
 * "Grabs" the forks by locking the mutexes.
 * 
 * @param philo The philo.
 */
static void	ft_grab_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->forks[philo->id]);
	if (philo->id == 0)
		pthread_mutex_lock(&philo->state->forks[philo->state->p_count - 1]);
	else
		pthread_mutex_lock(&philo->state->forks[philo->id - 1]);
	ft_mutex_print("[%3d] | [%d]: Picked up their forks 🍴\n", philo);
}

/**
 * "Drops" the forks by unlocking the mutexes.
 * 
 * @param philo The philo.
 */
static void	ft_drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->state->forks[philo->id]);
	if (philo->id == 0)
		pthread_mutex_unlock(&philo->state->forks[philo->state->p_count - 1]);
	else
		pthread_mutex_unlock(&philo->state->forks[philo->id - 1]);
}

/**
 * Will cause the philosopher to do some specific action.
 * 
 * @param philo The philo.
 * @param action The action the philo should do, EATING, SLEEPING or THINKING.
 */
static void	ft_philo_action(t_philo *philo, t_status action)
{
	if (action == EATING)
	{
		ft_grab_fork(philo);
		philo->last_meal_time = ft_time();
		philo->meals--;
		ft_mutex_print("[%3d] | [%d]: Is eating 🍝\n", philo);
		ft_sleep(philo->state->eating_time);
		ft_drop_fork(philo);
	}
	else if (action == SLEEPING)
	{
		ft_mutex_print("[%3d] | [%d]: Is sleeping 💤\n", philo);
		ft_sleep(philo->state->sleep_time);
	}
	else if (action == THINKING)
		ft_mutex_print("[%3d] | [%d]: Is thinking 💭\n", philo);
}

/**
 * This is life cycle of philo; eat, sleep, shit & die.
 *
 * @param philo The philo.
 */
void	*ft_cycle(void *arg)
{
	t_philo	*philo;

	philo = arg;
	ft_sleep((philo->id % 2) * philo->state->eating_time / 2);
	while (philo->state->status == RUNNING && philo->meals != 0)
	{
		ft_philo_action(philo, EATING);
		ft_philo_action(philo, SLEEPING);
		ft_philo_action(philo, THINKING);
	}
	return (NULL);
}
