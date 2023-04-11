/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:50:37 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/12 00:40:48 by htsang           ###   ########.fr       */
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
		malloc(sizeof(pthread_t) * amount_of_philosophers);
	if (!simulation->philosophers)
		return (SIMULATION_FAILURE);
	simulation->forks = \
		malloc(sizeof(pthread_mutex_t) * amount_of_philosophers);
	if (!simulation->forks)
	{
		free(simulation->philosophers);
		return (SIMULATION_FAILURE);
	}
	if (simulation_forks_create(simulation, amount_of_philosophers))
		return (SIMULATION_FAILURE);
	if (simulation_states_init(&simulation->states))
	{
		simulation_terminate(simulation, amount_of_philosophers);
		return (SIMULATION_FAILURE);
	}
	return (SIMULATION_SUCCESS);
}

t_simulation_status	simulation_wait_for_philosophers(\
const struct s_simulation *simulation, unsigned int amount_of_philosophers)
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
	free(simulation->forks);
	return (status);
}
