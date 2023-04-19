/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:30:38 by htsang            #+#    #+#             */
/*   Updated: 2023/04/19 17:19:23 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/reaper.h"
#include <pthread.h>
#include <unistd.h>

static struct s_reaper_report	*reaper_writes_report(struct s_reaper *reaper, \
unsigned int philosopher_id)
{
	struct s_reaper_report	*report;

	report = malloc(sizeof(struct s_reaper_report));
	if (!report)
		return (NULL);
	report->dead_philosopher_id = philosopher_id + 1;
	report->time_of_death = time_since(\
		reaper->simulation_states->start_time);
	return (report);
}

static struct s_reaper_report	*reaper_attempts_killing(\
struct s_reaper *reaper)
{
	unsigned int			philosopher_id;

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
			return (reaper_writes_report(reaper, philosopher_id));
		}
		philosopher_id++;
	}
	return (NULL);
}

static t_simulation_status	reaper_checks_must_eat(struct s_reaper *reaper)
{
	unsigned int	philosopher_id;

	philosopher_id = 0;
	while (philosopher_id < \
		reaper->simulation_settings->amount_of_philosophers)
	{
		if (reaper->philosophers_last_meal_times[philosopher_id] != 0)
			return (SIMULATION_FAILURE);
		philosopher_id++;
	}
	return (SIMULATION_SUCCESS);
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
	reaper_report = NULL;
	while (1)
	{
		reaper_report = reaper_attempts_killing(reaper);
		if (reaper_report)
			break ;
		usleep(1000);
		if (reaper_checks_must_eat(reaper) == SIMULATION_SUCCESS)
			break ;
	}
	free(reaper);
	return (reaper_report);
}
