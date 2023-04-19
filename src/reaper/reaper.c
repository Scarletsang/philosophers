/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:30:38 by htsang            #+#    #+#             */
/*   Updated: 2023/04/19 13:51:26 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/reaper.h"
#include <pthread.h>
#include <unistd.h>

static struct s_reaper_report	*reaper_attemps_killing(struct s_reaper *reaper)
{
	unsigned int			philosopher_id;
	struct s_reaper_report	*report;

	philosopher_id = 0;
	while (philosopher_id < \
		reaper->simulation_settings->amount_of_philosophers)
	{
		if (time_since(\
				reaper->philosophers_last_meal_times[philosopher_id]) >= \
				reaper->simulation_settings->time_to_die)
		{
			simulation_signal_wait(&reaper->simulation_states->kill_signal);
			simulation_signal_respond(&reaper->simulation_states->kill_signal, \
				SIMULATION_FAILURE);
			report = malloc(sizeof(struct s_reaper_report));
			if (!report)
				return (NULL);
			report->dead_philosopher_id = philosopher_id + 1;
			report->time_of_death = time_since(\
				reaper->simulation_states->start_time);
			return (report);
		}
		philosopher_id++;
	}
	return (NULL);
}

void	*reaper_routine(struct s_reaper *reaper)
{
	struct s_reaper_report	*reaper_report;

	if (simulation_signal_status_get(\
		&reaper->simulation_states->start_signal))
	{
		free(reaper);
		return (NULL);
	}
	while (1)
	{
		reaper_report = reaper_attemps_killing(reaper);
		if (reaper_report)
		{
			free(reaper);
			return (reaper_report);
		}
		usleep(1000);
	}
}
