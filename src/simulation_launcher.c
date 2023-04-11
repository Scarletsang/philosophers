/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_launcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:05:02 by htsang            #+#    #+#             */
/*   Updated: 2023/04/12 00:32:45 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/simulation_launcher.h"

static t_simulation_status	simulation_spawn_philosopher(\
struct s_simulation *simulation, \
const struct s_simulation_settings *settings, unsigned int philosopher_id)
{
	struct s_philosopher	*philosopher;

	philosopher = malloc(sizeof(struct s_philosopher));
	if (!philosopher)
		return (SIMULATION_FAILURE);
	philosopher_init(philosopher, simulation, settings, philosopher_id);
	if (pthread_create(&simulation->philosophers[philosopher_id - 1], NULL, \
		(void *(*)(void *)) philosopher_routine, (void *) philosopher))
	{
		free(philosopher);
		return (SIMULATION_FAILURE);
	}
	return (SIMULATION_SUCCESS);
}

t_philosophers_amount	simulation_start(struct s_simulation *simulation, \
const struct s_simulation_settings *settings)
{
	t_philosophers_amount	philosopher_id;

	philosopher_id = 1;
	pthread_mutex_lock(&simulation->states.start_signal.mutex);
	while (philosopher_id <= settings->amount_of_philosophers)
	{
		if (simulation_spawn_philosopher(simulation, settings, \
			philosopher_id))
		{
			simulation->states.start_time = time_get_current();
			simulation_signal_send(&simulation->states.start_signal, \
				SIMULATION_FAILURE);
			return (philosopher_id);
		}
		philosopher_id++;
	}
	simulation->states.start_time = time_get_current();
	simulation_signal_send(&simulation->states.start_signal, \
		SIMULATION_SUCCESS);
	return (philosopher_id);
}

int	philosophers_amount_meet_expectation(\
t_philosophers_amount philosophers_amount, \
const struct s_simulation_settings *settings)
{
	return (philosophers_amount == (settings->amount_of_philosophers + 1));
}
