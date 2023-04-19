/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_launcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:05:02 by htsang            #+#    #+#             */
/*   Updated: 2023/04/19 13:54:21 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/simulation_launcher.h"

static void	simulation_start_time_set(struct s_simulation *simulation, \
const struct s_simulation_settings *settings)
{
	t_philosophers_amount	i;

	simulation->states.start_time = time_now();
	i = 0;
	while (i < settings->amount_of_philosophers)
		simulation->philosophers_last_meal_times[i++] = \
			simulation->states.start_time;
}

t_philosophers_amount	simulation_start(struct s_simulation *simulation, \
const struct s_simulation_settings *settings)
{
	t_philosophers_amount	i;

	simulation_signal_wait(&simulation->states.start_signal);
	if (simulation_spawn_reaper(simulation, settings))
	{
		simulation_signal_respond(&simulation->states.start_signal, \
			SIMULATION_FAILURE);
		return (0);
	}
	i = 1;
	while (i <= settings->amount_of_philosophers)
	{
		if (simulation_spawn_philosopher(simulation, settings, i))
		{
			simulation_signal_respond(&simulation->states.start_signal, \
				SIMULATION_FAILURE);
			return (i);
		}
		i++;
	}
	simulation_start_time_set(simulation, settings);
	simulation_signal_respond(&simulation->states.start_signal, \
		SIMULATION_SUCCESS);
	return (i);
}

int	philosophers_amount_meet_expectation(\
t_philosophers_amount philosophers_amount, \
const struct s_simulation_settings *settings)
{
	return (philosophers_amount == (settings->amount_of_philosophers + 1));
}
