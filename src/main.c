/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsang <htsang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:20:29 by htsang            #+#    #+#             */
/*   Updated: 2023/04/19 17:09:57 by htsang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PHILOSOPHERS/simulation.h"
#include "PHILOSOPHERS/simulation/settings.h"
#include "PHILOSOPHERS/simulation_launcher.h"
#include <stdlib.h>

void	bury_dead_philosopher(struct s_reaper_report *reaper_report)
{
	if (reaper_report)
	{
		simulation_philosopher_status_print(reaper_report->time_of_death, \
			reaper_report->dead_philosopher_id, "died");
		free(reaper_report);
	}
}

void	*lonely_philosopher_routine(struct s_lonely_simulation *simulation)
{
	pthread_mutex_lock(&simulation->fork);
	simulation_philosopher_status_print(\
		time_since(simulation->start_time), 1, "has taken a fork");
	pthread_mutex_unlock(&simulation->fork);
	time_sleep(simulation->time_to_die);
	simulation_philosopher_status_print(\
		time_since(simulation->start_time), 1, "died");
	return (NULL);
}

int lonely_simulation(t_milliseconds time_to_die)
{
	struct s_lonely_simulation	lonely_simulation;

	lonely_simulation.time_to_die = time_to_die;
	lonely_simulation.start_time = time_now();
	pthread_mutex_init(&lonely_simulation.fork, NULL);
	pthread_create(&lonely_simulation.philosopher, NULL, \
		(void *(*)(void *)) lonely_philosopher_routine, \
		(void *) &lonely_simulation);
	pthread_join(lonely_simulation.philosopher, NULL);
	pthread_mutex_destroy(&lonely_simulation.fork);
	return (EXIT_SUCCESS);
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
		return (lonely_simulation(settings.time_to_die));
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
