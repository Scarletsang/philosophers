/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:30:38 by htsang            #+#    #+#             */
/*   Updated: 2023/04/18 22:07:40 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/reaper.h"
#include <pthread.h>
#include <unistd.h>

static unsigned int	*reaper_attemps_killing(struct s_reaper *reaper)
{
	unsigned int	philosopher_id;
	unsigned int	*dead_philosopher_id;

	philosopher_id = 0;
	while (philosopher_id < \
		reaper->simulation_settings->amount_of_philosophers)
	{
		if (time_since_simulation_get(\
				reaper->philosophers_last_meal_times[philosopher_id]) >= \
				reaper->simulation_settings->time_to_die)
		{
			simulation_signal_wait(&reaper->simulation_states->kill_signal);
			simulation_signal_respond(&reaper->simulation_states->kill_signal, \
				SIMULATION_FAILURE);
			dead_philosopher_id = malloc(sizeof(unsigned int));
			*dead_philosopher_id = philosopher_id + 1;
			return (dead_philosopher_id);
		}
		philosopher_id++;
	}
	return (NULL);
}

void	*reaper_routine(struct s_reaper *reaper)
{
	unsigned int	*dead_philosopher_id;

	if (simulation_signal_status_get(\
		&reaper->simulation_states->start_signal))
	{
		free(reaper);
		return (NULL);
	}
	while (1)
	{
		dead_philosopher_id = reaper_attemps_killing(reaper);
		if (dead_philosopher_id)
		{
			free(reaper);
			return (dead_philosopher_id);
		}
		usleep(1000);
	}
}
