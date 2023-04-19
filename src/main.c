/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:20:29 by htsang            #+#    #+#             */
/*   Updated: 2023/04/19 19:49:46 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/simulation.h"
#include "PHILOSOPHERS/simulation/settings.h"
#include "PHILOSOPHERS/simulation_launcher.h"
#include <stdlib.h>

static void	bury_dead_philosopher(struct s_reaper_report *reaper_report)
{
	if (reaper_report)
	{
		simulation_philosopher_status_print(reaper_report->time_of_death, \
			reaper_report->dead_philosopher_id, "died");
		free(reaper_report);
	}
}

int	main(int argc, const char **argv)
{
	const struct s_simulation_settings	settings;
	struct s_simulation					simulation;
	t_philosophers_amount				philosophers_amount;
	struct s_reaper_report				*reaper_report;

	if (simulation_settings_init((struct s_simulation_settings *) &settings, \
		argc, argv))
		return (EXIT_FAILURE);
	if (settings.amount_of_philosophers == 1)
		return (lonely_simulation_start(settings.time_to_die));
	if (simulation_init(&simulation, settings.amount_of_philosophers))
		return (EXIT_FAILURE);
	philosophers_amount = simulation_start(&simulation, &settings);
	reaper_report = simulation_wait_for_reaper(&simulation);
	if (philosophers_amount_meet_expectation(philosophers_amount, &settings))
		simulation_wait_for_philosophers(&simulation, \
			settings.amount_of_philosophers);
	else
		simulation_wait_for_philosophers(&simulation, philosophers_amount);
	bury_dead_philosopher(reaper_report);
	return (simulation_terminate(&simulation, settings.amount_of_philosophers));
}
