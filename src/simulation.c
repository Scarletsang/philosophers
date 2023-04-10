/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthonytsang <anthonytsang@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 20:50:37 by anthonytsan       #+#    #+#             */
/*   Updated: 2023/04/10 22:55:05 by anthonytsan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/simulation.h"

static t_simulation_status	simulation_mutexes_create(\
struct s_simulation *simulation, unsigned int amount_of_philosophers)
{
	unsigned int	i;

	i = 0;
	while (i < amount_of_philosophers)
	{
		if (pthread_mutex_init(&simulation->forks[i], NULL))
		{
			simulation_destroy(simulation, i);
			return (SIMULATION_FAILURE);
		}
		i++;
	}
	if (pthread_mutex_init(&simulation->is_printing, NULL))
	{
		simulation_destroy(simulation, i);
		return (SIMULATION_FAILURE);
	}
	return (SIMULATION_SUCCESS);
}

t_simulation_status	simulation_create(struct s_simulation *simulation, \
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
	if (simulation_mutexes_create(simulation, amount_of_philosophers))
	{
		return (SIMULATION_FAILURE);
	}
	simulation->start_time = time_get_current();
	return (SIMULATION_SUCCESS);
}

void	simulation_wait_for_philosophers(\
const struct s_simulation *simulation, unsigned int amount_of_philosophers)
{
	unsigned int	i;

	i = 0;
	while (i < amount_of_philosophers)
		pthread_join(&simulation->philosophers[i++], NULL);
}

void	simulation_destroy(const struct s_simulation *simulation, \
unsigned int amount_of_philosophers)
{
	unsigned int	i;

	i = 0;
	while (i < amount_of_philosophers)
		pthread_mutex_destroy(&simulation->forks[i++]);
	pthread_mutex_destroy(&simulation->is_printing);
	free(simulation->philosophers);
	free(simulation->forks);
}
