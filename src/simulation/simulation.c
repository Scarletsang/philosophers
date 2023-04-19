/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:50:37 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/19 13:42:32 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/simulation.h"

static t_simulation_status	simulation_forks_create(\
struct s_simulation *simulation, unsigned int amount_of_philosophers)
{
	unsigned int	i;

	i = 0;
	while (i < amount_of_philosophers)
	{
		if (pthread_mutex_init(&simulation->forks[i], NULL))
		{
			simulation_terminate(simulation, i);
			return (SIMULATION_FAILURE);
		}
		i++;
	}
	return (SIMULATION_SUCCESS);
}

t_simulation_status	simulation_init(struct s_simulation *simulation, \
unsigned int amount_of_philosophers)
{
	simulation->philosophers = \
		malloc((\
			sizeof(pthread_t) + \
			sizeof(pthread_mutex_t) + \
			sizeof(t_milliseconds)) * amount_of_philosophers);
	if (!simulation->philosophers)
		return (SIMULATION_FAILURE);
	simulation->forks = (pthread_mutex_t *) \
		(simulation->philosophers + amount_of_philosophers);
	simulation->philosophers_last_meal_times = (t_milliseconds *) \
		(simulation->forks + amount_of_philosophers);
	if (simulation_forks_create(simulation, amount_of_philosophers))
		return (SIMULATION_FAILURE);
	if (simulation_states_init(&simulation->states))
	{
		simulation_terminate(simulation, amount_of_philosophers);
		return (SIMULATION_FAILURE);
	}
	return (SIMULATION_SUCCESS);
}

struct s_reaper_report	*simulation_wait_for_reaper(\
struct s_simulation *simulation)
{
	struct s_reaper_report	*report;

	report = NULL;
	pthread_join(simulation->reaper, (void **) &report);
	return (report);
}

t_simulation_status	simulation_wait_for_philosophers(\
struct s_simulation *simulation, unsigned int amount_of_philosophers)
{
	unsigned int		i;
	t_simulation_status	status;

	i = 0;
	status = SIMULATION_SUCCESS;
	while (i < amount_of_philosophers)
	{
		if (pthread_join(simulation->philosophers[i++], NULL))
			status = SIMULATION_FAILURE;
	}
	return (status);
}

t_simulation_status	simulation_terminate(const struct s_simulation *simulation, \
unsigned int amount_of_philosophers)
{
	unsigned int		i;
	t_simulation_status	status;

	i = 0;
	status = SIMULATION_SUCCESS;
	while (i < amount_of_philosophers)
	{
		if (pthread_mutex_destroy(&simulation->forks[i++]))
			status = SIMULATION_FAILURE;
	}
	if (simulation_states_free(&simulation->states))
		status = SIMULATION_FAILURE;
	free(simulation->philosophers);
	return (status);
}
