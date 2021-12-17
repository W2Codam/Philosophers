/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 13:00:44 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/17 13:04:06 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//= This is where the shit happens. =//

#include "philo.h"

//= Extra utils =//

/**
 * Custom atoi64, any negative numbers or non numbers, will be caught as error.
 * 
 * @param str The string to be parsed.
 * @return False if conversion failed, true if it passed.
 */
static bool	ft_atoi64(const char *str, int64_t *out)
{
	size_t	i;
	int64_t	nbr;

	i = 0;
	nbr = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
	str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (false);
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	*out = nbr;
	return (true);
}

//= Main Section =//

/**
 * Philo constructor.
 * 
 * @param philo The philo output.
 * @param state The current game state.
 * @param id The id.
 * @return true or false depending on wether the creation succeeded.
 */
static bool	ft_new_philo(t_philo *philo, t_state *state, int32_t id)
{
	philo->id = id;
	philo->last_meal_time = state->start_time;
	philo->meals = state->eat_count;
	philo->state = state;
	if (pthread_create(&philo->thread, NULL, &ft_cycle, philo) != 0)
		return (false);
	//pthread_detach(philo->thread);
	return (true);
}

/**
 * Parses program arguments, any failure to parse will return false.
 */
static bool	ft_parse_args(int32_t argc, char **argv, t_state *state)
{
	if (ft_atoi64(argv[1], &state->p_count) && \
		ft_atoi64(argv[2], &state->death_time) && \
		ft_atoi64(argv[3], &state->eating_time) && \
		ft_atoi64(argv[4], &state->sleep_time))
	{
		if (argc - 1 == 5)
			return (ft_atoi64(argv[5], &state->eat_count));
		else
			state->eat_count = -1;
		return (true);
	}
	return (false);
}

/**
 * Initializes the game/simulation.
 * This is where all philosophers are created.
 * 
 * @param rules 
 * @return true 
 * @return false 
 */
static bool	ft_init_game(t_state *rules)
{
	int32_t	i;

	rules->status = RUNNING;
	rules->start_time = ft_time();
	rules->forks = malloc(rules->p_count * sizeof(pthread_mutex_t));
	if (!rules->forks)
		return (ft_perror("Error: Fork failure, not enough memory!"));
	rules->philos = malloc(rules->p_count * sizeof(t_philo));
	if (!rules->philos)
		return (ft_perror("Error: Philo failure, not enough memory!"));
	if (pthread_mutex_init(&rules->print_m, NULL) != 0)
		return (ft_perror("Error: Mutex intilization failure!"));
	if (pthread_mutex_init(&rules->death_m, NULL) != 0)
		return (ft_perror("Error: Mutex intilization failure!"));
	i = 0;
	while (i < rules->p_count)
		if (pthread_mutex_init(&rules->forks[i++], NULL) != 0)
			return (ft_perror("Error: Mutex intilization failure!"));
	i = -1;
	while (++i < rules->p_count)
		if (!ft_new_philo(&rules->philos[i], rules, i))
			return (ft_perror("Error: Philo failure!"));
	return (true);
}

//= Entry point =//

/**
 * Entry point for the program!
 *
 * @param argc Argument count.
 * @param argv Argument values.
 * @return The exit code.
 */
int32_t	main(int32_t argc, char **argv)
{
	t_state		*rules;
	pthread_t	monitor;

	if (argc - 1 < 4 || argc - 1 > 5)
		return (!ft_perror("Error: Invalid argument count!\n"));
	rules = memset(malloc(sizeof(t_state)), 0, sizeof(t_state));
	if (!ft_parse_args(argc, argv, rules))
		return (!ft_perror("Error: Invalid arguments!\n"));
	if (rules->p_count == 1)
	{
		printf("[0] | [1]: Picked up a fork 🍴\n");
		printf("\033[31m[%lld] | [1]: Is dead 💀!!!!\n\e[0m", rules->death_time);
		return (EXIT_SUCCESS);
	}
	if (!ft_init_game(rules))
		return (EXIT_FAILURE);
	if (pthread_create(&monitor, NULL, &ft_check_status, rules) != 0)
		return (ft_perror("Error: Failed to make monitor."));
	pthread_join(monitor, NULL);
	ft_cleanup(&rules);
	return (EXIT_SUCCESS);
}
